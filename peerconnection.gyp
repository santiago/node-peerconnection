# Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
#
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file in the root of the source
# tree. An additional intellectual property rights grant can be found
# in the file PATENTS.  All contributing project authors may
# be found in the AUTHORS file in the root of the source tree.

{
  'includes': [ 'third_party/webrtc/build/common.gypi', ],
  'variables': {
    'peerconnection_sample': 'third_party/libjingle/source/talk/examples/peerconnection',
  },  
  'targets': [
    {
      'target_name': 'peerconnection',
      'type': 'static_library',
      'dependencies': [
        'third_party/jsoncpp/jsoncpp.gyp:jsoncpp',
        'third_party/libjingle/libjingle.gyp:libjingle_peerconnection',
      ],
      'include_dirs': [
        'src',
        'src/modules/interface',
        'third_party/libjingle/source',
      ],
      'link_settings': {
        'ldflags': [
          '<!@(pkg-config --libs-only-L --libs-only-other gtk+-2.0 gthread-2.0)',
        ],
        'libraries': [
          '<!@(pkg-config --libs-only-l gtk+-2.0 gthread-2.0)',
          '-lX11',
          '-lXcomposite',
          '-lXext',
          '-lXrender',
        ],
      },
    }
  ]
}
