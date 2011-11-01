#!/bin/bash
clear
echo "Build knowledge base"
python rule_builder.py --fs_repo ../sui/kb --fs_repo_src ../repo
