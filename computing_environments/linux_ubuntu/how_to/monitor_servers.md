* Draft: 2020-07-30 (Thu)
# Monitor Servers

Google search: ICMP 감시
* [[서버] 서버 감시 기능](https://m.blog.naver.com/PostView.nhn?blogId=pjt3591oo&logNo=220547504579&proxyReferer=https:%2F%2Fwww.google.com%2F)

3종류의 서버 감시 기능
* L3 체크
* L4 체크
* L7 체크

부하분산 장치 (Load Balancer)
* 주기능: 서버에 부하를 분산
* 부기능: 서버의 상태를 감시
  * 한 서버에 장애가 발생하면, 세션을 할당하지 않는다.
* 모델별 제공 기능
  * BIG-IP는 Health Monitor 기능 제공
  * Ace 4700은 Health Check 기능 제공
  
<img src="images/figure5-2_advanced_n_1_redundancy.png">
Source: [Using F5 Big-IP as a Load Balancer for External Internet Connectivity](https://docs.solace.com/Solace-PubSub-Messaging-APIs/JavaScript-API/Web-Messaging-Concepts/Using-F5-Big-IP-as-a-Load.htm)

[F5 GLOSSARY > Load Balancer](https://www.f5.com/services/resources/glossary/load-balancer)
Some industry standard algorithms are:
* Round robin
* Weighted round robin
* Least connections
* Least response time
<img src="images/intro-load_balancer-f5_glossary.png">
