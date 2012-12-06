var webrtc = require('../webrtc');

//SERVER
// var WebSocketServer = require('ws').Server;

var server = require('./lib/webrtc.io').listen(6060);

// SERVER
server.rtc.on('connect', function(rtc) {
  // Client connected
  console.log('client connected')
});

server.rtc.on('send answer', function(rtc) {
  // answer sent
});

server.rtc.on('disconnect', function(rtc) {
  // Client disconnect 
});