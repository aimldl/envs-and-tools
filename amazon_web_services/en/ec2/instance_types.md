##### aimldl/aws/ec2/instance_types.md

## Amazon EC2 Instance Types
M < C < P << X1

Source: [Amazon EC2 Instance Types](https://aws.amazon.com/ec2/instance-types/)

***Accelerated Computing***
P2

|   Instance   |   GPUs   |   vCPU   |   Mem (GiB    |   GPU Memory (GiB)   |   Network Performance   |
| ------------ | -------- | -------- | ------------- | -------------------- | ----------------------- |
| p2.xlarge    | 1        | 4        | 61            | 12                   | High                    |
| p2.8xlarge   | 8        | 32       | 488           | 96                   | 10 Gigabit              |
| p2.16xlarge  | 16       | 64       | 732           | 192                  | 25 Gigabit              |

***Memory Optimized***
X1

| Instance    | vCPU | Mem (GiB) | SSD Storage (GB) | Dedicated EBS Bandwidth (Mbps) | Network Performance |
| ----------- | ---- | --------- | ---------------- | ------------------------------ | ------------------- |
| x1.16xlarge | 64   | 976       | 1 x 1,920        | 7,000                          | 10 Gigabit          |
| x1.32xlarge | 128  | 1,952     | 2 x 1,920        | 14,000                         | 25 Gigabit          |
