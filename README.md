# FakeDos

*This repository was part of the group assignment in CSC3002 (Spring 2020) in CUHKsz.*

A fake CLI multi-task multi-user operating system.

# Manuals
## Environment Preparation
Use Qt Creator 4.11.0 (Community) on Windows 10 to open the project `CSC3002Project.pro` and click the green run button.
## Testing Features
### General
The general functionalities of FakeDos can be tested by using different commands. Type help and you will see all available commands and their descriptions. More specifically, you should see all those changes you made to FakeDos by using the following commands:
- `show_content`
- `list_task`
- `ls_u`
- `ls_lu`
### Memorizable User Information
FakeDos will remember the user information including the last working directory be- fore a user logs out. You can test this feature by create a user, change a directory,log out or exit FakeDos, and log in with the same user again.

### Multi-user and Multi-task OS
FakeDos supports multiple online users at the same time. You can use the command change_user, log in with a different user, and use ls_lu to see all online users. You can even try to run some apps and you can see all apps can exist simultaniously.

### Memory Management and Memory Limit
In FakeDos, logging in users and running apps will consume memory. You can check the detailed memory usage using the command list_task. The memory management module will also guarantee that the memory usage will not exceed the memory limit.

# Introduction
In this project, we built a TUI, multi-task, multi-user operating system based on Windows called FakeDos.
This OS is be implemented with the following modules:
- Memory management module
- Task management module
- File management module
- Application management module
- User management module

## Memory management module
Memory management module adopts json data structure as the memory map to
store data of each tasks created by different users and applications. Memory data is stored and passed using a json-styled string named `jsonmem`. This string is parsed each time by function from `jsoncpp` library. The total memory space of fakeDos is set to be `0x7FF` Bytes.
Below is an `jsonmem` sample string used by the system. Actually this sample is in-visable for users, a better interface is implemented by `list_task` commend of fakeOS.
```json
{
	”1622650073” :
		{
			”text1” : ”a”, 
			”text2” : ”s”, 
			”text3” : ”d”, 
			”text4” : ”f”, 
			”text5” : ”g”, 
			”text6” : ”h”, 
			”textsize” : ”6”
		},
	”16807” :
		{
			”text1” : ”q”,
			”text2” : ”w”, 
			”text3” : ”e”, 
			”text4” : ”r”, 
			”text5” : ”t”, 
			”text6” : ”y”, 
			”textsize” : ”6”
		},
	”282475249” :
		{
			”goal” : ”285719”, 
			”guess” : ”999”, 
			”round” : ”3”
		},
	” taskmem ” :
		{
			”1622650073” : 168, 
			”16807” : 168, 
			”282475249” : 72
		},
	”user” :
		{
			”Alice” : 495,
			”Bob” : 423 
		}
}
```
Each unique task is identified by a unique `taskid` serve as memory address for os to access data stored in memory. For memory usage of each task and user, `"taskid" : int` (taskmemory) is stored under `"taskmem"`, and ”username” : int (usermemory) is stoerd under `”user”`. For data storage of each task, it follows `”taskid” : ”variable- name” : ”value”` structure.

### Functions description and implementation:
#### `init_mem`
Initialize memory data by defining `”user”` and `”taskmem”` part in `jsonmem` string.
#### `user_mem_alloc`
Called when an user log into the fakeDos. By setting memory usage of current user to `0xFF`, it represent a fake memory usage of OS itself.
#### `task_mem(taskid, taskmem, username)`
Called during the blocking operation of tasks. Record memory usage of current task at `[”taskmem”][taskid]`. Add this usage amount to user memory for the user of this task.
#### `tsk_data_read`
Find and return specific values inside json memory by `taskid` and key.
Called during a task is wake up after blocking. This function return the previous stored data to the task in the string form. The task convert those strings to other data type according to the purpose of task.
#### `task_data_write`
Called when a task is blocking. The task need to pass all data in the string form one by one to this function. After checking if there is enough memory space by calling limit_check function, it save string value of input data using a unique key name under this taskid. Memory space used by writing data is added to memory usage of this task and user as well.
#### `user_mem_free`
Free memory space allocated to the input username by setting `[”user”][username]` to be 0. Called when a user log out of fakeDos. It means all memory data of this user is wiped.
#### `task_mem_free`
Free memory space allocated to the input `taskid` by clear all data under this `taskid`, setting memory usage of this task to be zero, and deduct this free memory size from user memory space.
#### `limit_check`
Check whether an memory writing operation is about to excel the total memory space.
This can happened when a new user log in ot a task saving data into memory. This function add new demanded memory size with current memory usage of all logined users to campare
#### `get_task_mem`
Return memory usage of given taskid.
#### `get_user_mem`
Return memory usage of given username.

## Task management module
Task management module is the basic framework of FakeDos. It provides some functions that allow users to create, kill, block, wake up and look all the tasks while using FakeDos. One feature of task management module is that it arranges multiple tasks as ready states or running states to increase efficiency. It can also save the data in the tasks after the system shuts down, when user later wake up the task, it can show user the saved content.
### Data struct used
We used a PCB structure to represent a task, which contains the information of username, appname, task id and the state of the task.
A PCB list `mem[100]` is used to represent memory. Tasks in memory have 3 states: 1 for running, 2 for block and 3 for ready. The 0 state of the task means that the task is not in memory.
Three queues are used to help the task management working. Tasks of running state are in running queue, tasks of ready state are in ready queue, tasks of block state are in block queue.
### Function description and implementation:
#### `create_task`
This function creates a task, which returns the task id if task is created success- fully. This function checks the remaining memory space before task creation. If there is no remaining memory space, the task creation will fail and returns false.
#### `display`
This function display the task information by the below syntax.
#### `block`
This function blocks the task by changing the state of a task, according to the id, and user name. Only the user who create the task have the right to block the task. The data of the blocked task are saved for later usage.
#### `Wake_up`
This function wakes the blocked task by changing the state of a task,according to the id. Only the user who create the task have the right to wake up the task.
#### `kill`
This function kills the task by changing the state of a task and free the space occupied by the task. Only the user who create the task have the right to kill the task.

## File management module
The file management of fake DOS is based on “fake route” (in this section, we use “route” and “path” interchangeably). In our design, a fake route always starts with “root”, for example: root\users\A\B. Essentially, “root” is a directory called “fakeDos”, which is created at the beginning of this program. You can find it under the debug folder created by Qt. The program keeps track of fake route, and convert it into “real route” whenever needed. Based on the real route, the program will call corresponding system commands (cmd commands) and therefore, record users’ operations on file system.
File management module implements the following commands:
### Create a file or directory
The corresponding commands are “make_file (name.type)” and “make_dir (name/path)”.
When using “make_file”, the input should be a file name with a specific file type (e.g: .txt), and the corresponding file will be created under current working space.  
When using “make_dir”, the input can simply be a name or a relative path. If it is a name, then the directory will be made under current working space; if it is a path, then the directory will be made recursively base on current working space. For example:  
Current working space: root\A  
Command: make_dir B create a directory B under root\A;  
Command: make_dir B\C create directory B under A, and then create directory C under B.  
This part is done by using cmd commands “cd.>” and “mkdir”.  
### Delete a file or directory
The corresponding commands are “del_file (name.type)” and “del_dir (name/- path)”.
Similar to “make_file” and “make_dir”, users can delete a specific file or directory under current working space. Particularly, if the input for “del_dir” is a relative path, the program will go to the end of the path and delete the target directory.
This part is done by using cmd commands “del” and “rd”.
### Change current working space to a specific path
The corresponding command is “change_path (name/path)”.
If the input is a name, the program will search through current working space and change to the corresponding directory.
If the input is an absolute path (note that it has to be an absolute path, i.e. start with “root\”), the program will directly change to that path.
Short cut inputs:
“u”: go to upper-level directory: root\A\B root\A “rt” go to root directory: root\A\B\C root
This part is essentially an operation on strings. The program will take the “current route” of user, and change it to the “target route” specified by user’s input. This function will also call “write_user” method, which is implemented in user management module, to write the change into “users.txt” (created at the beginning of program). Therefore, the change on users’ current route can be recorded and tracked anytime.
### Show the content of current directory
The corresponding command is “show_content”.
This command will print out all the file names and directory names of current working space.
This part is implemented using “_finddata_t” structure, which is included in `<io.h>`. The program will go to user’s “current route”, and store all the file names and directory names inside a vector. After that, the vector will be printed out.
### Copy a file or directory to a target directory
The corresponding command is “copy (name1) (name/path 2)”.
This command can copy a file or a directory (name1) to a target directory (name/path 2).
If the target directory and the file/directory you want to copy are under same directory, you can simply specify the name of target directory. Otherwise, you need to specify the absolute path of target directory (start with “root\”).
Besides, you have to specify the type (e.g: .txt) when copying files.
This part is implemented using cmd command “xcopy”. However, we noticed that when using “xcopy” to copy directory, the system simply copies the con- tent of a directory, rather than the directory itself. To solve that problem, we first created a folder with the same name under target directory, and then “xcopy” the directory to the folder that newly created.
### Move a file or directory to a target directory
The corresponding command is “move (name1) (name/path 2)”.
This command can move a file or a directory (name1) to a target directory (name/path 2). The rules are similar to “copy” command.
This part is implemented using cmd command “move”.
### Read or write in a text file
The corresponding commands are “read (name)” and “write (name)”.
These commands are implemented using file streams, and only support fun- damental “read” and “write” operations. Users can only write in a text file from the bottom, and are not allowed to edit its content. To edit a text, users can download the application “TextEditor”, which is out of the scope of file management.
Besides, please note that users only need to specify the file name (without “.txt”).
## Application management module
Application management module provide some basic functions that allow users to get their apps from a marketplace that is predefined by our team.

### Commands syntax, description and implementation:
#### `install (app name).app`
Install an app under the current directory. The app should be available in the App Store provided by the OS.
Implementation: Called the make_file command provided by the file man- agement module and create a file called “app name.app” under the current directory.
#### `appstore`
List all the apps available in the App Store with the names and descriptions.
Implementation: I made a list of available app names and their descriptions as global variable. This command prints out all those informaiton.

## User management module
User management module is the basic framework of FakeDos. It provides some fucntions that allow users to create or delete their identity while using FakeDos. One feature of FakeDos is that it allows multiple online users at the same time. It can also remember the user information after the system shuts down, especially the working directory of the user before it logged out last time.
### Commands syntax, description and implementation:
#### `create_user (user name) (password)`
Create a user.
Implementation: Push the information of the new user to a list which saves all avaiable users.
#### `delete_user (user name)`
Delete a user. It will ask for the password for the user that is going to be deleted. Noted that a user can not delete itself.
Implementation: Delete the information from the list of users. Also, it will kill all the tasks if the deleted user is online and is running some apps.
#### `log_in (user name) (password)`
Log in as the given user name.
Implementation: Check if the user name and password matches. If so, change the current user to this user and change the current directory to the working directory of this user before it logged out last time.
#### `log_out`
log out the current user.
Implementation: change the current user to NULL, and save the working directory to users.txt under the folder system.
#### `change_user`
Go back to user selection without logging out the current user.
Implementation: leave all the running tasks going on and let the user to change its indentity.
#### `ls_u`
List all the available users.
Implementation: I made a list that saves all users that was created. • ls_lu
List all the logged in users.
Implementation: I made a list that saves all logged in users.12
## System commands
### Command syntax and description:
#### `exit`
Shut down FakeDos.
#### `help`
Show the name, description and syntax of all commands.

## Applications Available in App Store
### textEditor
This text editor is implemented using linked list data structure (taught in text book p583-599). Users can move the cursor, and input or delete the text after it.
### guessGame
A guessing game that let the user to guess the value of a randomly generated number. Every round if the guess is wrong, the game will tell the player if the guess is larger or smaller than the goal number.
### todoList
This app allows user to write down the thing to do and tick it if done. Users can look the whole list at any time.


# 一个假的命令行操作系统

基本逻辑：
“操作系统”启动后，其实是进入了一个while循环，在每一轮，我们接收用户的一个指令，并作出需要的操作。我们模仿DOS，在每一轮循环用户都会“在”某个目录下。（其实就是输出一段路径的字符串假装我们真的在那个目录下）

任务1: 用户管理模块
by: @watanabexia

	所谓用户，我们其实就是在启动“系统”后给每个用户分配各自的一个“桌面”（创建一个文件夹作为某个用户的桌面，并在之后用户登录时将“当前路径”引导至用户的文件夹），每个用户都有对所有资源和命令的使用权。（当然，如果觉得任务太轻也可以再添加不同用户的不同权限。如果想加，这一部分应该需要后续再一起讨论）

	功能实现的最低要求：

	创建用户
	登陆用户
	切换用户（optional）
	注销用户
	删除用户
	记录已经登陆的用户
	记录存在的用户
	
任务2: 文件管理模块
by: @GaliLeo03

我们所做的任何文件操作都将被限制在某个文件夹中。

![image](http://github.com/watanabexia/CSC3002Project/raw/master/images/document_architecture.jpeg)

	功能实现的最低要求：
	
	创建文件/文件夹
	删除文件/文件夹
	剪切文件
	复制文件
	
任务3: 应用管理模块
by: @LeNNon0822

	我们所谓的应用，全部都是一些具有特定功能的函数。打开应用，实则是进入了某个函数。安装应用，我们模仿linux，通过install指令来安装我们预先准备好的一些应用。所谓安装，其实就是在某个路径下创建一个.app作为结尾的文件，用这个文件的名字来作为启动应用的命令。
	
	功能实现的最低要求：
	
	安装应用
	启动应用
	卸载应用
	
	写几个非常基础的应用（最基础可以基础到输入半径返回周长）


任务4: 进程管理模块
by: @slowhite

	我们在启动应用的时候，首先要告诉进程管理模块说我们建立了一个新进程。
	
	功能实现的最低要求：
	
	建立进程
	杀死进程
	
任务5: 内存管理模块
by: @J3pHR3-Y

	我们在启动应用后，函数总是需要建立一些变量的。我们在建立变量的时候，要向内存管理模块确认还有足够的内存。
	
	功能实现的最低要求：
	
	确认内存是否足够
	记录内存的使用
    记录内存的释放
