@echo off
chcp 65001 >nul
cd /d "C:\Users\raymond\Desktop\STM32智能小车\STM32F103\USER"

:: 确保初始化并重新绑定为 SSH 地址
if not exist ".git" (
    git init
)
git remote remove origin 2>nul
git remote add origin git@github.com:raymondkkxx/USER.git
git branch -M main

:: 暂存所有更改
git add .

:: 提示输入 Commit 信息（直接回车则自动使用当前时间戳）
set "commit_msg="
set /p commit_msg="请输入 Commit 信息: "
if "%commit_msg%"=="" (
    set commit_msg=Auto commit: %date:~0,10% %time:~0,8%
)

:: 提交并推送到 main 分支
git commit -m "%commit_msg%"
git push -u origin main --force

pause