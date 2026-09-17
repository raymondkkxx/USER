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

:: 暂存并提交当前更改
git add .
git commit -m "Auto commit: %date:~0,10% %time:~0,8%"

:: 强制推送到 main 分支（解决 non-fast-forward 冲突）
git push -u origin main --force

pause