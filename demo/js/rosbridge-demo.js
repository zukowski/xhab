jQuery(function() {
  connection = new WebSocket("ws://127.0.0.1:9090")  
  subscribe_message = {'op': 'subscribe', 'topic': '/array', 'type': 'std_msgs/Int32MultiArray'}
  connection.onmessage = function(incoming_message) { console.log("Received:", incoming_message.data); }
  connection.onopen = function() {
    connection.send(JSON.stringify(subscribe_message))
  }
})
