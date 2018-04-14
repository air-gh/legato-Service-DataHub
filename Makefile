
TARGET ?= localhost

.PHONY: all dataHub appInfoStub sensor actuator
all: dataHub appInfoStub sensor actuator

dataHub:
	mkapp -t localhost dataHub.adef -i $(LEGATO_ROOT)/interfaces/supervisor

appInfoStub:
	mkapp -t localhost test/appInfoStub.adef -i $(LEGATO_ROOT)/interfaces/supervisor -i $(CURDIR)

sensor:
	mkapp -t localhost test/sensor.adef -i $(PWD)

actuator:
	mkapp -t localhost test/actuator.adef -i $(PWD)

.PHONY: clean
clean:
	rm -rf _build* *.update docs backup

.PHONY: start stop
start: stop all
	# LE_LOG_LEVEL=DEBUG startlegato
	startlegato
	sdir bind "<$(USER)>.le_appInfo" "<$(USER)>.le_appInfo"
	sdir bind "<$(USER)>.sensord.sensor.io" "<$(USER)>.io"
	sdir bind "<$(USER)>.actuatord.actuator.io" "<$(USER)>.io"
	sdir bind "<$(USER)>.dhubToolAdmin" "<$(USER)>.admin"
	sdir bind "<$(USER)>.dhubToolIo" "<$(USER)>.io"
	sdir bind "<$(USER)>.dhubToolQuery" "<$(USER)>.query"
	test/supervisor
	_build_dataHub/localhost/app/dataHub/staging/read-only/bin/dhub set bufferSize count 100
	_build_dataHub/localhost/app/dataHub/staging/read-only/bin/dhub set backupPeriod count 20
	_build_dataHub/localhost/app/dataHub/staging/read-only/bin/dhub set source /obs/count /app/sensor/counter/value
	_build_dataHub/localhost/app/dataHub/staging/read-only/bin/dhub set default /app/sensor/counter/period 4
	_build_dataHub/localhost/app/dataHub/staging/read-only/bin/dhub set default /app/sensor/counter/enable true

stop:
	stoplegato

IFGEN_FLAGS = --gen-interface --output-dir _build_docs

.PHONY: docs
docs:
	mkdir -p _build_docs
	ifgen $(IFGEN_FLAGS) admin.api
	ifgen $(IFGEN_FLAGS) io.api
	ifgen $(IFGEN_FLAGS) query.api
	doxygen
