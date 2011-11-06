#!/bin/bash
clear
echo "Copy test knowlegde base into repository"
mkdir "../repo/main/test"
cp -r -f "../test/kb" "../repo/main/test"
echo "Build knowledge base"
python rule_builder.py --fs_repo ../bin/kb --fs_repo_src ../repo
