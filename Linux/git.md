> 内容源自[廖雪峰的Git教程](https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000)

* [一.git配置](一git配置)
	- [1.配置git用户名和邮箱](1配置git用户名和邮箱)
* [二.仓库](二仓库)
	- [1.创建git仓库](1创建git仓库)
	- [2.查看仓库状态](2查看仓库状态)
	- [3.远程仓库](3远程仓库)

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