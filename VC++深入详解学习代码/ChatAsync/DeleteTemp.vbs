''''''''''''''''''''''''''''''''''''
' DeleteTemp.VBS
' 说明:ATM辅助工具-删除临时文件目录及临时文件
' Date:   11/27/2014
' author: alex tong
' 功能:
' 寻找删除的临时文件及目录,将文件及目录移动到deltemp目录
' 并copy到当前目录下的temp目录
''''''''''''''''''''''''''''''''''''
'初始化准备
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
'可以在此处添加修改临时文件目录及例外设置
TempDir=",Debug,Release,ipch,_UpgradeReport_Files,"
TempFile=",bak,ncb,sdf,db,cod,bsc,pch,idb,sbr,scc,opt,plg,tlog,old,"
ExceptionKey=",dll,lib,exe,map,pdb,res,ocx,zip,rar,"

'--------------------主流程----------------------- 
Run()
'释放资源
Set myFso=Nothing

'--------------------Function--------------------
'查找文件并copy
Function Run()
		'On Error Resume Next
		Dim strBakFolderPath
		Dim strCurrFolderPath
		Dim returnValue
		'弹出删除的临时目录，临时文件类型及例外
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
		
		
		'查找当前目录的子目录及文件进行开始删除及备份
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
	 
		'备份路径
		strDesFoldPath=strBakPath & Right(strCurrFolderPath,Len(strCurrFolderPath)-Len(sourceFolderPath))
		
		'查找目标文件
		If sourceFolderPath <> strCurrFolderPath Then 
			Set fc = objFolder.Files
	    For Each f1 in fc
	      exName=UCase(myFso.GetExtensionName(f1.Path))
	      
	      If  (delFile = "*" or InStr(delFile,","&exName&",") > 0) and InStr(delExcept,","&exName&",") = 0 Then
	      	fSrcPath=f1.Path
	      	fDesPath=strBakPath & Right(fSrcPath,Len(fSrcPath)-Len(sourceFolderPath))
	      			'svn的DB文件不删除
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
    '子目录查找
    Dim folderc
		Dim folder1
		Set folderc = objFolder.SubFolders
    For Each folder1 in folderc 
    	folderName=UCase(folder1.Name)
    	'例外目录不需要再查找
    	If folderName <> "DELTEMP"  Then
	    	If  delDir = "*" or InStr(delDir,","&folderName&",") > 0  Then
			 		FindFileAndDel sourceFolderPath,strBakPath,folder1,"*","*",delExcept
	    	Else
	      	FindFileAndDel sourceFolderPath,strBakPath,folder1,delDir,delFile,delExcept
				End If
			End If
    Next
		
End Function
'************公共方法**********************

'屏幕输出及Log文件输出信息
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

'建立File路径目录
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
'循环建立目录
Sub FEachCreateFolder(Folder)
        Dim RegEx, arrFolder, thisFolder
        
        '使用正则表达式搜索出每级目录 便于依次创建
        Set RegEx = New RegExp
        RegEx.Pattern = "[^\\]+\\" '搜索所有的非\字符和\ 如d:\a\网络\cc 则结果为 d:\  a\  网络\  cc
        RegEx.IgnoreCase = True
        RegEx.Global = True
        Set arrFolder = RegEx.Execute(Folder)
        Set RegEx = Nothing
        For Each SubFolder In arrFolder
            thisFolder = thisFolder & SubFolder '一层一层的推进
            If Not myFso.FolderExists(thisFolder) Then
                myFso.CreateFolder(thisFolder) '如果该层不存在则创建
            End If
            
        Next
End Sub




