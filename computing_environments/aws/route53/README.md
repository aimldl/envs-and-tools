##### aimldl/aws/route53/README.md

# Amazon Route53
## How to Register a Domain Name
Refer to a tutorial to [Register a Domain Name with Amazon Route 53](https://aws.amazon.com/getting-started/tutorials/get-a-domain/).

1. Sign into https://aws.amazon.com/
2. In the AWS Management Console, enter "Route 53" to the dialog box under "Find Services".
<img src='images/amazon_route53-aws_management_console.png'>

 Then you will enter the dashboard for Route 53.
3. In the Route 53 dashboard, type in a domain name to check if it is available.

<img src='images/amazon_route53-register_domain.png'>

Typically, it is likely the domain name you want is unavailble. So be creative to find an alternative domain name.
<img src='images/amazon_route53-choose_a_domain_name.png'>
In my case, I wanted aimldl.com, but chose mldl.org instead because I can create a link http://ai.mldl.org.

4. Once the domain name is decided, click "Continue" and follow the procedure.
5. A pending request is created. Note the domain is not created instantly.
<img src='images/amazon_route53-pending_requests.png'>
6. In several minutes, the registration is complete and an email is sent to the registered email.

<img src='images/amazon_route53-email_successfully_registered_with_route_53.png'>

* [Working with Resource Record Sets](https://docs.aws.amazon.com/Route53/latest/DeveloperGuide/rrsets-working-with.html)
* [Amazon Web Services Customer Support](https://console.aws.amazon.com/support/cases#/create?issueType=customer-service)
