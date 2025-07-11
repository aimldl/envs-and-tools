# Update & Clean Up
- Created: 2025-07-11 (Fri)
- Updated: 2025-07-11 (Fri)

## Update & upgrade 
```bash
sudo apt update
sudo apt upgrade
```
## Update Anaconda
If Anaconda is installed, run:
```bash
conda update --all
```
## Clean up
First, update your package list and clean up apt
```bash
sudo apt update
sudo apt autoremove -y
sudo apt clean
```
## Clean up Anaconda
```bash
conda clean --all -y
```
