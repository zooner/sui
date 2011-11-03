#!/bin/bash
clear
echo "Copy test knowlegde base into repository"
cp -r -f "../test/kb" "../repo/main/test"
echo "Build knowledge base"
python rule_builder.py --fs_repo ../sui/kb --fs_repo_src ../repo
