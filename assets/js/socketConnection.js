// let dnsName = 'onestep.local';
let dnsName = "192.168.4.1";
var connection = new WebSocket(`ws://${dnsName}:81/`);

console.log("connection : ");
console.log(connection);

connection.onopen = function () {
  console.log("WebSocket connection is open now.");

  document.getElementById(
    "ConnectionStatus"
  ).innerHTML = `<i class="icon bi bi-wifi status-icon"></i>
                    <div class="status-label">Connection</div>
                    <div id="signal" class="status-value">Good</div>`;
};

connection.onerror = function (error) {
  console.log("WebSocket error: ", error);

  document.getElementById(
    "ConnectionStatus"
  ).innerHTML = `<i class="bi bi-wifi-off status-icon"></i>
                    <div class="status-label">Connection</div>
                    <div id="signal" class="status-value">Error</div>`;
};

connection.onclose = function () {
  console.log("WebSocket connection closed.");

  document.getElementById(
    "ConnectionStatus"
  ).innerHTML = `<i class="bi bi-wifi-off status-icon"></i>
                    <div class="status-label">Connection</div>
                    <div id="signal" class="status-value">Closed</div>`;
};

connection.onmessage = function (event) {
  console.log("Message from server: ", event.data);
};
