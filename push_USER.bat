@echo off
chcp 65001 >nul
cd /d "C:\Users\raymond\Desktop\STM32智能小车\STM32F103\USER"

:: 检查并初始化 Git 仓库与远程分支
if not exist ".git" (
    git init
    git branch -M main
    git remote add origin https://github.com/raymondkkxx/USER.git
)

:: 暂存、提交并推送到 GitHub
git add .
git commit -m "Auto commit: %date:~0,10% %time:~0,8%"
git push -u origin main

pause