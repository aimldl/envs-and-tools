##### aimldl/aws/eks/README.md

# [Amazon EKS (Amazon Elastic Kubernetes Service)](https://aws.amazon.com/eks/?nc1=h_ls)

EKS is the Kubernetes service by Amazon. You can not only build a new Kebernetes cluster, but also migrate any standard Kubernetes application without needing to refactor the code.

<img src="https://d1.awsstatic.com/re19/FargateonEKS/Landing-Page-Diagram-EKS@2x.e7f23e44e4b460fc9f46d5f77a3a8d60807dc111.png">

Through Amazon EKS, EKS clusters can be run with Amazon EC2 or  [AWS Fargate](https://aws.amazon.com/fargate/) (serverless compute for containers). Fargate removes the need to provision and manage servers, lets you specify and pay for resources per application, and improves security through application isolation by design. 

For details about EKS, refer to [Amazon EKS (Amazon Elastic Kubernetes Service)](https://aws.amazon.com/eks/?nc1=h_ls). The use cases from the webpage is copied and pasted below.

> ## Use cases
>
> ### Hybrid Deployment
>
> You can use EKS on [AWS Outposts](https://aws.amazon.com/outposts/) to run containerized applications that require low latencies to on-premises systems. AWS Outposts is a fully managed service that extends AWS infrastructure, AWS services, APIs, and tools to virtually any connected site. With EKS on Outposts, you can manage containers on-premises with the same ease as you manage your containers in the cloud.
>
> ### Machine Learning
>
> You can use Kubeflow with EKS to model your machine learning workflows and efficiently run distributed training jobs using the latest EC2 GPU-powered instance types. You can also use [AWS Deep Learning Containers](https://aws.amazon.com/machine-learning/containers/) for running training and inferences in TensorFlow on EKS.
>
> ### Batch Processing
>
> You can run sequential or parallel batch workloads on your EKS cluster using the Kubernetes Jobs API. Using EKS, you can plan, schedule, and execute your batch computing workloads across the full range of AWS compute services and features, such as Amazon EC2, Fargate, and Spot Instances.
>
> ### Web Applications
>
> You can build web applications that automatically scale up and down and run in a highly available configuration across multiple Availability Zones. By running on EKS, your web applications benefit from the performance, scale, reliability, and availability of the AWS. Additionally, your services get out-of-the-box integrations with AWS networking and security services, such as Application Load Balancers for load distribution of your web application and VPC for networking.