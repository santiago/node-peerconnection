{
  # "includes": ["deps/webrtc/webrtc.gyp"],
  'includes': [ 'deps/webrtc/third_party/webrtc/build/common.gypi', ],
  "targets": [
    {
      "target_name": "webrtc",
      "sources": [ 
        "src/bindings.cc", 
        "src/peer_connection_client.cc", 
        "src/node_peer_connection_client.cc",
        "deps/webrtc/third_party/libjingle/source/talk/examples/peerconnection/client/defaults.cc"
      ],

      "dependencies": [
        'deps/webrtc/third_party/jsoncpp/jsoncpp.gyp:jsoncpp',
        'deps/webrtc/third_party/libjingle/libjingle.gyp:libjingle_peerconnection',
      ],

      "include_dirs": [
        "deps/webrtc/third_party/libjingle/source/talk/examples/peerconnection/client",
        "deps/webrtc/third_party/webrtc",
        "deps/webrtc/third_party/libjingle/source"
      ]
    }
  ]
}