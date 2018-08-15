> 内容源自[廖雪峰的Git教程](https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000)

* [一.git配置](#一git配置)
	- [1.配置git用户名和邮箱](#1配置git用户名和邮箱)
* [二.仓库](#二仓库)
	- [1.创建git仓库](#1创建git仓库)
	- [2.查看仓库状态](#2查看仓库状态)
	- [3.远程仓库](#3远程仓库)
    - [4.协同工作](#4协同工作)
    - [5.使用GitHub](#5使用github)
* [三.版本控制](#三版本控制)
    - [1.添加或删除修改](#1添加或删除修改)
    - [2.提交版本](#2提交版本)
    - [3.改动查询](#3改动查询)
    - [4.版本回退](#4版本回退)
    - [5.查看历史提交](#5查看历史提交)

<br>
<br>

# 一.git配置

优先级：`--local > --global > --system`

> 用了`--global`这个参数，表示你这台机器上所有的Git仓库都会使用这个配置

### 1.配置git用户名和邮箱

```bash
git config --global user.name        # 查看
git config --global user.name 用户名  # 修改
git config --global user.email       # 查看
git config --global user.email 邮箱   # 修改
```

<br>

# 二.仓库

### 1.创建git仓库

```bash
git init 仓库名  #创建一个git仓库
git init        #将一个项目转化为使用git管理（创建.git目录）
```

示例：

![](../pic/git-1.png)

目录结构：

```bash
project
   |------.git
            |--------branches
            |--------config        #仓库的配置文件
            |--------description
            |--------HEAD
            |--------hooks
            |--------info
            |--------objects
            |--------refs
```

> 隐藏目录`.git`不算工作区，而是Git的版本库

### 2.查看仓库状态

```bash
git status
```

### 3.远程仓库

> 最早，肯定只有一台机器有一个原始版本库，此后，别的机器可以“克隆”这个原始版本库，而且每台机器的版本库其实都是一样的，并没有主次之分
> 
> 实际情况往往是这样，找一台电脑充当服务器的角色，每天24小时开机，其他每个人都从这个“服务器”仓库克隆一份到自己的电脑上，并且各自把各自的提交推送到服务器仓库里，也从服务器仓库中拉取别人的提交
> 
> GitHub就是提供Git仓库托管服务的，所以，只要注册一个GitHub账号，就可以免费获得Git远程仓库，即Github为我们的git仓库提供了一个远程仓库，有了这个远程仓库，妈妈再也不用担心我的硬盘了

#### 1）为本地与GitHub的通信配置ssh

**本地git仓库和GitHub上的远程仓库之间的传输是通过SSH加密的，所以，需要一点设置**：

1. **创建ssh key**：
    ```bash
    ssh-keygen -t rsa -C "youremail@example.com"
    ```
2. **登录你的GitHub帐号，`Settings -> SSH and GPG keys -> new SSH key` ，将id_rsa.pub的内容复制进去**

> 为什么GitHub需要SSH Key呢？因为GitHub需要识别出你推送的提交确实是你推送的，而不是别人冒充的，而Git支持SSH协议，所以，GitHub只要知道了你的公钥，就可以确认只有你自己才能推送

#### 2）让本地git仓库和远程仓库同步

> 在有了本地git仓库后，还需创建对应的远程仓库

1. **在GitHub上创建远程仓库**（如果已有则省略）
2. **为本地仓库设置远程仓库信息**（如果同时需要为本地仓库添加多个远程仓库（如果github+码云），则可以将`origin`分别换成`github`和`gitee`，推送操作时也要修改`origin`。添加后，远程库的名字就是`origin`，这是Git默认的叫法，也可以改成别的，但是`origin`这个名字一看就知道是远程库）
    ```bash
    git remote add origin https://github.com/用户名/仓库名
    ```
    * **删除本地仓库的远程仓库信息**：`git remote remove origin`
    * **修改远端地址**：`git remote set-url 新地址`
    * **查看远程仓库信息**：`git remote -v`
3. **将本地git仓库push到远程仓库**
    ```bash
    # 由于远程库是空的，我们第一次推送master分支时，加上了-u参数,Git不但会把本地的
    # master分支内容推送的远程新的master分支，还会把本地的master分支和远程的master
    # 分支关联起来，在以后的推送或者拉取时就可以简化命令
    git push [-u] origin 分支名
    ```

并不是一定要把本地分支往远程推送。哪些分支需要推送、哪些不需要呢？

* `master`：主分支，要时刻与远程同步
* `dev`：开发分支，团队所有成员都需要在上面工作，所有也需要与远程同步
* `bug`：只用于在本地修复bug，就没必要推送到远程了，除非老板要看看你每周修复了几个bug

### 4.协同工作

拉取分支：

```bash
git pull
```

`git clone`时，默认情况下只能看到本地的`master`分支。如果要在`dev`分支上开发，就必须创建远程`origin`的`dev`分支到本地，可以使用如下命令创建本地`dev`分支：

```bash
git checkout -b dev
```

将本地`dev`分支与远程`origin/dev`分支关联起来：

```bash
git branch --set-upstream dev origin/dev
```

### 5.使用GitHub

Bootstrap的官方仓库twbs/bootstrap、你在GitHub上克隆的仓库my/bootstrap，以及你自己克隆到本地电脑的仓库，他们的关系就像下图显示的那样：

![](../pic/git-2.png)

如果你想修复bootstrap的一个bug，或者新增一个功能，立刻就可以开始干活，干完后，往自己的仓库推送

**如果你希望bootstrap的官方库能接受你的修改，你就可以在GitHub上发起一个pull request。当然，对方是否接受你的pull request就不一定了**

<br>

# 三.版本控制

隐藏目录`.git`不算工作区，而是Git的版本库。版本库里存了很多东西，其中最重要的就是**称为stage（或者叫index）的暂存区**。还有Git为我们自动创建的第一个分支`master`，以及指向`master`的一个指针叫`HEAD`

![](../pic/git-3.png)

### 1.添加或删除修改

将修改添加到暂存区：

```bash
git add 文件/目录
```

从暂存区删除修改：

```bash
git rm --cached 文件/目录
```

以下命令可以将暂存区的修改重置，暂存区的改变会被移除到工作区：

```bash
git rest HEAD [文件名]
```

以下命令可以丢弃工作区的修改：

```bash
git checkout -- [文件名]
```

如果刚对一个文件进行了编辑，可以撤销文件的改变，回到编辑开始。命令其实起到“一键恢复”的作用，还可用于“误删恢复”。可以在 `git reset HEAD [文件名]` 后使用

### 2.提交版本

如果修改了readme.txt，添加了文件LICENSE，并将2者添加到暂存区后，暂存区的状态就变成这样：

![](../pic/git-4.png)

使用commit提交修改，实际上就是把暂存区的所有内容提交到当前分支：

```bash
git commit -m '信息'
```

![](../pic/git-5.png)

> commit相当于游戏里面一次存档。对应一个版本

### 3.改动查询

```bash
git diff [选项]           # 查看工作区中的修改
git diff [选项] --staged   # 查看已添加到暂存区的修改
git diff [选项] HEAD       # 查看当前所有未提交的修改

选项：
    --color-words： 颜色
    --stat：        不显示具体修改，只显示修改了的文件
```

### 4.版本回退

```bash
git reset --hard 版本ID/HEAD形式的版本

git reset --hard HEAD      # 当前版本
git reset --hard HEAD^     # 上一个版本
git reset --hard HEAD^^    # 上上个版本
git reset --hard HEAD~n    # 前n个版本
```

如果回到过去的版本，想要回到原来新的版本：

* 如果终端未关，可以找到新版本的id，通过上述命令回去新版本
* 如果终端已关，`git reflog`查看版本，再通过上述命令回去新版本

### 5.查看历史提交

```bash
git log [选项]

选项：
    --online：只显示提交提示信息
    --stat：添加每次提交包含的文件信息
    --path：查看每次提交改变的内容
    --graph
```

**加文件名可以显示具体文件相关的所有提交信息**