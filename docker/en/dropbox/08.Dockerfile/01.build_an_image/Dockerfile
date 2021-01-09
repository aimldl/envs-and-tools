# Step 0. Install based on the official CentOS image
FROM centos:latest

# Step 1. Add the maintainer/creator info
MAINTAINER Tae-Hyung T Kim, mrtonnet@gmail.com

# Step 2. Install Apache
# RUN yum install -y httpd
# or equivalently
RUN ["yum", "install", "-y", "httpd"]

# Step 3. Install NGINX
# Run yum install -y nginx
# or equivalently
RUN ["rpm", "-Uvh", "http://nginx.org/packages/mainline/centos/7/x86_64/RPMS/nginx-1.11.0-1.el7.ngx.x86_64.rpm"]  
RUN ["RUN", "yum", "install", "-y", "nginx"]  

# Step 4. Execute the Apache server httpd
# CMD /usr/sbin/httpd -D FOREGROUND
# or equivalently
CMD ["CMD", "/usr/sbin/httpd", "-D", "FOREGROUND"] 

