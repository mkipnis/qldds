project(%(libname)s) :  dcps_java {

  idlflags     +=  -I$(QLDDS_ROOT)/qldds_utils -Wb,export_macro=QLDDS_Export\
                 -Wb,stub_export_include=$(QLDDS_ROOT)/qldds_utils/qldds_Export.h \
                  -Wb,stub_export_macro=QLDDS_Export
  dcps_ts_flags+=  -I$(QLDDS_ROOT)/qldds_utils -Wb,export_macro=QLDDS_Export \
                  -Wb,export_macro=QLDDS_Export
  idl2jniflags +=  -I$(QLDDS_ROOT)/qldds_utils -Wb,export_macro=QLDDS_Export \
                 -Wb,stub_export_include=$(QLDDS_ROOT)/qldds_utils/qldds_Export.h \
                  -Wb,stub_export_macro=QLDDS_Export
  dynamicflags += QLDDS_BUILD_DLL
  includes      += $(TAO_ROOT)/orbsvcs $(QLDDS_ROOT)/qldds_utils
  libpaths      += $(QLDDS_ROOT)/qldds_utils
  libs          += qldds_utils_java
  requires += tao_orbsvcs

  specific {
    jarname     = %(libname)s
  }

  TypeSupport_Files {
        %(idlfile)s
  }
}
