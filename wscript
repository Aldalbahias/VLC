# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

def configure(conf):
    conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('vlcnew', ['core','network', 'mpi', 'mobility', 'propagation','point-to-point'])
    module.source = [
        'model/vlcnew.cc',
        'helper/vlcnew-helper.cc',
        'helper/vlcChannelHelper.cc',
        'helper/vlcDeviceHelper.cc',
        'model/vlcNetDevice.cc',
        'model/vlcchannel.cc',
        'model/vlcMobilityModel.cc',
        'model/VlcPropagationLoss.cc',
        'model/vlcNetDeviceRX.cc',
        'model/vlcNetDeviceTX.cc',
        'model/VLC_SNR.cc' ,
        'model/VLC-error-model.cc' ,
        ]

    module_test = bld.create_ns3_module_test_library('vlcnew')
    module_test.source = [
        'test/vlcnew-test-suite.cc',
        ]

    headers = bld(features='ns3header')
    headers.module = 'vlcnew'
    headers.source = [
        'model/vlcnew.h',
        'helper/vlcnew-helper.h',
        'helper/vlcChannelHelper.h',
        'helper/vlcDeviceHelper.h',
        'model/vlcNetDevice.h',
        'model/vlcchannel.h',
        'model/vlcMobilityModel.h',
        'model/VlcPropagationLoss.h',
        'model/vlcNetDeviceRX.h',
        'model/vlcNetDeviceTX.h',
        'model/VLC_SNR.h' ,
        'model/VLC-error-model.h' ,
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

    # bld.ns3_python_bindings()

