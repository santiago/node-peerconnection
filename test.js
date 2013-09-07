var SegfaultHandler = require('segfault-handler');

SegfaultHandler.registerHandler();

var PeerConnectionClient = require('./build/Release/obj.target/webrtc').PeerConnectionClient;

var client = new PeerConnectionClient();

client.connect('localhost', 8888, 'node@ubuntu');
