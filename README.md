## Collect metrics from process with DSO injection

Use LD_PRELOAD to inject DSO into process. After a thread will be created to collect some metrics and push it to CloudWatch. 
Actual model works with Nginx only. All the global variables from the stub modules are collected and pushed to CloudWatch. 

This model should work for any other collect on global variables or function returns. 

Depends on aws-sdk-cpp (https://github.com/aws/aws-sdk-cpp/), which depends on cmake 3.0. 

### Usage
```
LD_PRELOAD=/path/to/sweet.so nginx
```
