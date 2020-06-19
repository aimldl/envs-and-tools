% test_send_email
%
% This m-file is a small script to test how to send an email.
% Refer to "How do I use SENDMAIL to send email from MATLAB 7.2 (R2006a)
% via the GMail server?" at http://www.mathworks.com/support/solutions/data/1-3PRRDV.html
%
% Written by Tae-Hyung D. Kim, tk424@mst.edu
% Last updated:  May. 29, 2008 (Thu)
% First written: May. 29, 2008 (Thu)

clear all;
% Define these variables appropriately:
mail = 'tkim.hobbies@gmail.com';                % Your GMail email address
password = 'skxogud2';                          % Your GMail password

% Then this code will set up the preferences properly:
setpref('Internet','E_mail',mail);
setpref('Internet','SMTP_Server','smtp.gmail.com');
setpref('Internet','SMTP_Username',mail);
setpref('Internet','SMTP_Password',password);
props = java.lang.System.getProperties;
props.setProperty('mail.smtp.auth','true');
props.setProperty('mail.smtp.socketFactory.class', 'javax.net.ssl.SSLSocketFactory');
props.setProperty('mail.smtp.socketFactory.port','465');

% Send the email
sendmail('tkim.hobbies@gmail.com','Test from MATLAB','Hello! This is a test from MATLAB!')

