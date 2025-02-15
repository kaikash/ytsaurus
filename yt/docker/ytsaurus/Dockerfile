FROM jupyter/minimal-notebook:1aac87eb7fa5

USER root

WORKDIR /tmp

ARG YTSERVER_ALL_PATH=ytserver-all
ARG CHYT_CONTROLLER_PATH=chyt-controller
ARG CLICKHOUSE_TRAMPOLINE_PATH=clickhouse-trampoline
ARG YTSERVER_CLICKHOUSE_PATH=ytserver-clickhouse
ARG YTSERVER_LOG_TAILER_PATH=ytserver-log-tailer
ARG INIT_OPERATION_ARCHIVE_PATH=init_operation_archive
ARG YT_PATH=yt

ARG YTSERVER_ALL_CREDITS_PATH=ytserver-all.CREDITS
ARG CHYT_CONTROLLER_CREDITS_PATH=chyt-controller.CREDITS
ARG YTSERVER_CLICKHOUSE_CREDITS_PATH=ytserver-clickhouse.CREDITS
ARG YTSERVER_LOG_TAILER_CREDITS_PATH=ytserver-log-tailer.CREDITS

ARG DRIVER_BINDINGS_PACKAGE_PATH=ytsaurus_native_driver-1.0.0-cp39-cp39-linux_x86_64.whl

COPY ${YTSERVER_ALL_PATH} /usr/bin/ytserver-all

RUN ln /usr/bin/ytserver-all /usr/bin/ytserver-master && \
    ln /usr/bin/ytserver-all /usr/bin/ytserver-clock && \
    ln /usr/bin/ytserver-all /usr/bin/ytserver-discovery && \
    ln /usr/bin/ytserver-all /usr/bin/ytserver-node && \
    ln /usr/bin/ytserver-all /usr/bin/ytserver-job-proxy && \
    ln /usr/bin/ytserver-all /usr/bin/ytserver-exec && \
    ln /usr/bin/ytserver-all /usr/bin/ytserver-proxy && \
    ln /usr/bin/ytserver-all /usr/bin/ytserver-http-proxy && \
    ln /usr/bin/ytserver-all /usr/bin/ytserver-tools && \
    ln /usr/bin/ytserver-all /usr/bin/ytserver-scheduler && \
    ln /usr/bin/ytserver-all /usr/bin/ytserver-controller-agent && \
    ln /usr/bin/ytserver-all /usr/bin/ytserver-query-tracker

# CHYT bits and pieces.
COPY ${CHYT_CONTROLLER_PATH} /usr/bin/chyt-controller
COPY ${CLICKHOUSE_TRAMPOLINE_PATH} /usr/bin/clickhouse-trampoline
COPY ${YTSERVER_CLICKHOUSE_PATH} /usr/bin/ytserver-clickhouse
COPY ${YTSERVER_LOG_TAILER_PATH} /usr/bin/ytserver-log-tailer

# Static binary built in arcadia.
COPY ${INIT_OPERATION_ARCHIVE_PATH} /usr/bin/init_operation_archive

# SPYT files
COPY spyt_release/home/spark/conf/releases/1.67.0/metrics.properties /usr/bin/metrics.properties
COPY spyt_release/home/spark/conf/releases/1.67.0/solomon-agent.template.conf /usr/bin/solomon-agent.template.conf
COPY spyt_release/home/spark/conf/releases/1.67.0/solomon-service-master.template.conf /usr/bin/solomon-service-master.template.conf
COPY spyt_release/home/spark/conf/releases/1.67.0/solomon-service-worker.template.conf /usr/bin/solomon-service-worker.template.conf

COPY spyt_release/home/spark/spark/releases/3.2.2-fork-1.67.0/spark.tgz /usr/bin/spark.tgz

COPY spyt_release/home/spark/spyt/releases/1.67.3/spark-yt-data-source.jar /usr/bin/spark-yt-data-source.jar
COPY spyt_release/home/spark/spyt/releases/1.67.3/spyt.zip /usr/bin/spyt.zip

COPY spyt_release/home/spark/bin/releases/1.67.0/spark-yt-launcher.jar /usr/bin/spark-yt-launcher.jar

# CREDITS files with licenses for all binaries
COPY ${YTSERVER_ALL_CREDITS_PATH} /usr/bin/ytserver-all.CREDITS
COPY ${CHYT_CONTROLLER_CREDITS_PATH} /usr/bin/chyt-controller.CREDITS
COPY ${YTSERVER_CLICKHOUSE_CREDITS_PATH} /usr/bin/ytserver-clickhouse.CREDITS
COPY ${YTSERVER_LOG_TAILER_CREDITS_PATH} /usr/bin/ytserver-log-tailer.CREDITS

# TODO: remove vim and lynx
RUN apt-get update && apt-get install -y \
  curl \
  less \
  gdb \
  lsof \
  strace \
  telnet \
  dnsutils \
  iputils-ping \
  lsb-release \
  openjdk-11-jdk \
  vim \
  lynx

# This is required for jobs, using yson format in python 3.
# TODO: To be replaced by public pip.
# https://pypi.yandex-team.ru/simple/ \
RUN pip install -i https://test.pypi.org/simple/ \
    --extra-index-url https://pypi.org/simple/ \
    ytsaurus-client \
    ytsaurus-yson

# Default python to be used by python3 jobs, for compatibility with jupyter tutorial.
RUN ln -s /opt/conda/bin/python3.7 /usr/bin/python3 -f

RUN /opt/conda/bin/python3.7 -m pip install -i https://test.pypi.org/simple/ \
    --extra-index-url https://pypi.yandex-team.ru/simple/ \
    ytsaurus-client \
    ytsaurus-local \
    ytsaurus-spyt==1.67.3

# Local built package with native driver bindings
COPY ${DRIVER_BINDINGS_PACKAGE_PATH} ytsaurus_native_driver-1.0.0-py2.py3-none-any.whl
RUN /opt/conda/bin/python3.7 -m pip install /tmp/ytsaurus_native_driver-1.0.0-py2.py3-none-any.whl \
    --extra-index-url https://pypi.org/simple/
RUN rm /tmp/ytsaurus_native_driver-1.0.0-py2.py3-none-any.whl

# Add symlink for yt
RUN ln -s /opt/conda/bin/yt /usr/bin/yt -f

RUN ln -s /usr/lib/jvm/java-11-openjdk-amd64 /opt/jdk11

# Force lsb_release to use python it was born to use.
RUN sed -i 's/python3/python3.8/' /usr/bin/lsb_release

# TODO: add opportunity to get this files in opensource
# Static binaries & shared libraries built in arcadia.
# In order to obtain them, run the following command in yt/yql/package:
#   ya package package.json --raw-package-path yql_package
# And move the resulting directory to the context of docker build.
COPY yql_package/ytserver-yql-agent /usr/bin/
COPY yql_package/mrjob /usr/bin/
COPY yql_package/lib*.so /usr/lib/yql/
