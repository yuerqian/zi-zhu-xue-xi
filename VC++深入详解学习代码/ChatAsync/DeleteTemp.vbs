''''''''''''''''''''''''''''''''''''
' DeleteTemp.VBS
' ˵��:ATM��������-ɾ����ʱ�ļ�Ŀ¼����ʱ�ļ�
' Date:   11/27/2014
' author: alex tong
' ����:
' Ѱ��ɾ������ʱ�ļ���Ŀ¼,���ļ���Ŀ¼�ƶ���deltempĿ¼
' ��copy����ǰĿ¼�µ�tempĿ¼
''''''''''''''''''''''''''''''''''''
'��ʼ��׼��
Dim myFso
Set myFso =CreateObject("Scripting.FileSystemObject")

Dim RunPath
RunPath="./deltemp"
If myFso.FolderExists(RunPath) = False Then
	 myFso.CreateFolder(RunPath)
End If 
If myFso.FileExists(RunPath+"/log.txt") = True Then
	 myFso.DeleteFile(RunPath+"/log.txt")
End If


Dim TempDir,TempFile,ExceptionKey
'�����ڴ˴�����޸���ʱ�ļ�Ŀ¼����������
TempDir=",Debug,Release,ipch,_UpgradeReport_Files,"
TempFile=",bak,ncb,sdf,db,cod,bsc,pch,idb,sbr,scc,opt,plg,tlog,old,"
ExceptionKey=",dll,lib,exe,map,pdb,res,ocx,zip,rar,"

'--------------------������----------------------- 
Run()
'�ͷ���Դ
Set myFso=Nothing

'--------------------Function--------------------
'�����ļ���copy
Function Run()
		'On Error Resume Next
		Dim strBakFolderPath
		Dim strCurrFolderPath
		Dim returnValue
		'����ɾ������ʱĿ¼����ʱ�ļ����ͼ�����
		returnValue=msgbox("delete Dir:"&TempDir&chr(10)&chr(13)&"Delete File Type:"&TempFile&Chr(10)&chr(13)&"Exception Key:"&ExceptionKey,vbYesNo,"Pls config delete?")
		If returnValue = vbNo Then 
			Exit Function
		End If
		
		
		strCurrFolderPath=myFso.GetAbsolutePathName(".")
		If strCurrFolderPath = myFso.GetDriveName(strCurrFolderPath) Then
			WriteInfo("not supper search on dirver")
			Exit Function
		End If 
		WriteInfo("begin find file of dir[" & strCurrFolderPath & "]...")
		strBakFolderPath=strCurrFolderPath+"\deltemp" 
		If myFso.FolderExists(strBakFolderPath) = False Then
			 myFso.CreateFolder(strBakFolderPath)
		End If 
		
		
		'���ҵ�ǰĿ¼����Ŀ¼���ļ����п�ʼɾ��������
		 FindFileAndDel strCurrFolderPath,strBakFolderPath,strCurrFolderPath,UCase(TempDir),UCase(TempFile),UCase(ExceptionKey)
		
		
		
End Function
Function FindFileAndDel(sourceFolderPath,strBakPath,strCurrFolderPath,delDir,delFile,delExcept)
		Dim fc
		Dim f1
		Dim fDate
		Dim fSrcPath
		Dim fDesPath
		Dim strDesFoldPath
		Dim objFolder
	  Dim exName
		Dim folderName
		On Error Resume Next
		Set objFolder=myFso.GetFolder(strCurrFolderPath)
	 
		'����·��
		strDesFoldPath=strBakPath & Right(strCurrFolderPath,Len(strCurrFolderPath)-Len(sourceFolderPath))
		
		'����Ŀ���ļ�
		If sourceFolderPath <> strCurrFolderPath Then 
			Set fc = objFolder.Files
	    For Each f1 in fc
	      exName=UCase(myFso.GetExtensionName(f1.Path))
	      
	      If  (delFile = "*" or InStr(delFile,","&exName&",") > 0) and InStr(delExcept,","&exName&",") = 0 Then
	      	fSrcPath=f1.Path
	      	fDesPath=strBakPath & Right(fSrcPath,Len(fSrcPath)-Len(sourceFolderPath))
	      			'svn��DB�ļ���ɾ��
	      			if exName <> "db" and objFolder.Name <> ".svn" then
		      			If myFso.FolderExists(strDesFoldPath) = False Then
			 				FEachCreateFolder(fDesPath)
						End If
						WriteInfo("wait process file[" & fSrcPath & "]")
						myFso.CopyFile fSrcPath,fDesPath
						myFso.DeleteFile fSrcPath
						WriteInfo("file[" & fSrcPath & "]delete And bak to ["& fDesPath &"]")
					end if
	    	End If
	    Next
  	End If
    '��Ŀ¼����
    Dim folderc
		Dim folder1
		Set folderc = objFolder.SubFolders
    For Each folder1 in folderc 
    	folderName=UCase(folder1.Name)
    	'����Ŀ¼����Ҫ�ٲ���
    	If folderName <> "DELTEMP"  Then
	    	If  delDir = "*" or InStr(delDir,","&folderName&",") > 0  Then
			 		FindFileAndDel sourceFolderPath,strBakPath,folder1,"*","*",delExcept
	    	Else
	      	FindFileAndDel sourceFolderPath,strBakPath,folder1,delDir,delFile,delExcept
				End If
			End If
    Next
		
End Function
'************��������**********************

'��Ļ�����Log�ļ������Ϣ
Function WriteInfo(strInfo)
	Dim strTempInfo
	Dim myFile
	Set myFile = myFso.OpenTextFile(RunPath+"/log.txt",8, True,0) 
	strTempInfo=CStr(strInfo)
	strTempInfo=FormatDateTime(Date()+Time()) & "-----" & strTempInfo
	myFile.WriteLine(strTempInfo)
	myFile.Close
	WScript.Echo strTempInfo
	Set myFile = Nothing
End Function

'����File·��Ŀ¼
Function BusBuildFolder(strFolderPath)
		If strFolderPath = myFso.GetDriveName(strFolderPath) Then
			Exit Function
		End If
		If myFso.FolderExists(strFolderPath) = True Then
				Exit Function
		Else
			BusBuildFolder(myFso.GetParentFolderName(strFolderPath))
			myFso.CreateFolder(strFolderPath)
		End If 
End Function
'ѭ������Ŀ¼
Sub FEachCreateFolder(Folder)
        Dim RegEx, arrFolder, thisFolder
        
        'ʹ��������ʽ������ÿ��Ŀ¼ �������δ���
        Set RegEx = New RegExp
        RegEx.Pattern = "[^\\]+\\" '�������еķ�\�ַ���\ ��d:\a\����\cc ����Ϊ d:\  a\  ����\  cc
        RegEx.IgnoreCase = True
        RegEx.Global = True
        Set arrFolder = RegEx.Execute(Folder)
        Set RegEx = Nothing
        For Each SubFolder In arrFolder
            thisFolder = thisFolder & SubFolder 'һ��һ����ƽ�
            If Not myFso.FolderExists(thisFolder) Then
                myFso.CreateFolder(thisFolder) '����ò㲻�����򴴽�
            End If
            
        Next
End Sub




