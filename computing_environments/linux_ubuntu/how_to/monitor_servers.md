* Draft: 2020-07-30 (Thu)
# How to Monitor Servers

> Google search: ICMP 감시
> * [[서버] 서버 감시 기능](https://m.blog.naver.com/PostView.nhn?blogId=pjt3591oo&logNo=220547504579&proxyReferer=https:%2F%2Fwww.google.com%2F)

Load balancer BIG-IP provides "Health Monitor" functionality while Ace 4700 provides "Health Check" functionality.
Q: What's the difference between "Health Monitor" and "Health Check".

## Server Monitoring
* L3 Check
* L4 Check
* L7 Check

## Load Balancer
A load balancer distributes load to servers. Some industry standard algorithms are:
* Round robin
* Weighted round robin
* Least connections
* Least response time

<img src="images/intro-load_balancer-f5_glossary.png">

Source: [F5 GLOSSARY > Load Balancer](https://www.f5.com/services/resources/glossary/load-balancer)

As a side job, a load balancer minitors the status of servers. When an error occurs at a server, no session is assigned to the server. 
  
<img src="images/figure5-2_advanced_n_1_redundancy.png">
Source: [Using F5 Big-IP as a Load Balancer for External Internet Connectivity](https://docs.solace.com/Solace-PubSub-Messaging-APIs/JavaScript-API/Web-Messaging-Concepts/Using-F5-Big-IP-as-a-Load.htm)

## fping
> Google search: fping
> * [FPING](https://fping.org/fping.1.html)
> * [Fping – A High Performance Ping Tool for Linux](https://www.tecmint.com/ping-multiple-linux-hosts-using-fping/)
>    fping is a small command line tool to send ICMP (Internet Control Message Protocol) echo request to network hosts, similar to ping, but much higher performing when pinging multiple hosts.

> * [fping](https://fping.org/)



## References
* [[서버] 서버 감시 기능](https://m.blog.naver.com/PostView.nhn?blogId=pjt3591oo&logNo=220547504579&proxyReferer=https:%2F%2Fwww.google.com%2F)
* [F5 GLOSSARY > Load Balancer](https://www.f5.com/services/resources/glossary/load-balancer)
* [Using F5 Big-IP as a Load Balancer for External Internet Connectivity](https://docs.solace.com/Solace-PubSub-Messaging-APIs/JavaScript-API/Web-Messaging-Concepts/Using-F5-Big-IP-as-a-Load.htm)
