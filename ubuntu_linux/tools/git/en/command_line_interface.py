##### aimldl > computing_environments > git > command_line_interface.py

# Git with Command Line Interface

### To create a new repository on the command line
```bash
echo "# documents" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/aimldl/documents.git
git push -u origin master
```

### To push an existing repository from the command line
```bash
git remote add origin https://github.com/aimldl/documents.git
git push -u origin master
```
