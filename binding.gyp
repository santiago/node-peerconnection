{
  "includes": [ "/home/santiago/webrtc/trunk/third_party/webrtc/build/common.gypi" ],
  "variables": {
    "webrtc_home": "/home/santiago/webrtc/trunk",
    "webrtc_root%": "/home/santiago/webrtc/trunk/third_party/webrtc"
  },
  "targets": [
    {
      "target_name": "binding",
      "sources": [ "src/bindings.cc", "src/PeerConnection.cc" ],
      
      "dependencies": [
        "<(webrtc_home)/third_party/jsoncpp/jsoncpp.gyp:jsoncpp",
        "<(webrtc_home)/third_party/libjingle/libjingle.gyp:*"
      ],
      "include_dirs": [
        "<(webrtc_home)/third_party/libjingle/source"
        "<(webrtc_home)/third_party/webrtc",
        "<(webrtc_home)/third_party/webrtc/modules/interface",

      ],
      "link_settings": {
        "ldflags": [],
        "libraries": [
          "-lX11",
          "-lXcomposite",
          "-lXext",
          "-lXrender"
        ]
      }
    }
  ]
}