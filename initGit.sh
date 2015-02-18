#!/bin/bash
#initGit.sh

git clone https://github.com/LSDev8/PSAR-Kilobot
git remote -v
cd PSAR-Kilobot
git remote add upstream https://github.com/LSDev8/PSAR-Kilobot
git remote -v
git branch develop origin/develop
cd ..
