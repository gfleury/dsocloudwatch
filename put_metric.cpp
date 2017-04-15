#include <aws/monitoring/CloudWatchClient.h>
#include <aws/monitoring/model/PutMetricDataRequest.h>
#include <aws/core/Aws.h>
#include <iostream>

Aws::CloudWatch::CloudWatchClient cw;
Aws::SDKOptions options;

void init_aws_sdk() {
	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
	Aws::InitAPI(options);
}

int put_metric_cw(char *nameSpace, char *metricName, char *dimensionName, char *dimensionValue, int value, const char *errMsg) {

	Aws::CloudWatch::Model::Dimension dimension;
	dimension.SetName(dimensionName);
	dimension.SetValue(dimensionValue);

	Aws::CloudWatch::Model::MetricDatum datum;
	datum.SetMetricName(metricName);
	datum.SetUnit(Aws::CloudWatch::Model::StandardUnit::None);
	datum.SetValue(value);
	datum.AddDimensions(dimension);

	Aws::CloudWatch::Model::PutMetricDataRequest request;
	request.SetNamespace(nameSpace);
	request.AddMetricData(datum);

	auto outcome = cw.PutMetricData(request);
	if (!outcome.IsSuccess()) {
  	  	std::cout << "Failed to put sample metric data:" <<
	        outcome.GetError().GetMessage() << std::endl;
		if (errMsg)
			errMsg = outcome.GetError().GetMessage().c_str();
		return 1;
	} else {
		std::cout << "Successfully put sample metric data" << std::endl;
		return 0;
	}
}

void shutdown_aws_sdk() {
	Aws::ShutdownAPI(options);
}
