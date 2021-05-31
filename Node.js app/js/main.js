const SerialPort = require('serialport')

var scene, renderer, camera;
var cube;
var controls;

var statusText = document.getElementById("statusText");

const port = new SerialPort('COM4', {
  baudRate: 115200
})

renderer = new THREE.WebGLRenderer({ antialias: true });
var width = window.innerWidth;
var height = window.innerHeight;
renderer.setSize(width, height);
document.body.appendChild(renderer.domElement);

scene = new THREE.Scene();

var cubeGeometry = new THREE.BoxGeometry(10, 10, 10);
var cubeMaterial = new THREE.MeshBasicMaterial({ color: 0x1ec876 });
cube = new THREE.Mesh(cubeGeometry, cubeMaterial);

cube.position.set(0, 0, 0);
scene.add(cube);

camera = new THREE.PerspectiveCamera(45, width / height, 1, 10000);
camera.position.y = 60;
camera.position.z = 140;
camera.lookAt(new THREE.Vector3(0, 0, 0));

controls = new THREE.OrbitControls(camera, renderer.domElement);

const size = 100;
const divisions = 10;

const gridHelper = new THREE.GridHelper(size, divisions);
scene.add(gridHelper);

const axesHelper = new THREE.AxesHelper(50);
scene.add(axesHelper);



function animate() {
  controls.update();
  requestAnimationFrame(animate);
  renderer.render(scene, camera);
}

function sendJson(num, baseDegrees, arm1Degrees, arm2Degrees, delay, waitTime = 10) {
  let delayRead = document.getElementById("delayInput").value

  let message = {
    action: num,
    baseDegrees: baseDegrees,
    arm1Degrees: arm1Degrees,
    arm2Degrees: arm2Degrees,
    speed: delayRead,
    waitTime: waitTime 
  }

  let stringMessage = JSON.stringify(message)

  console.log('Writing json to port...')

  port.write(stringMessage, function (err) {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
    console.log('message written')
    statusText.innerHTML = "Message written: "
  })

}

function sendTest() {
  console.log('test')

  sendJson(1, null, null, null, null, null)
}

function zeroArm() {
  console.log('test')

  sendJson(2, null, null, null, 10, null)
}

function maxArm() {
  console.log('test')

  sendJson(3, 170, 85, null, 10, null)
}

function sendToPos() {
  let baseDegrees = document.getElementById("baseInput").value;
  let arm1Degrees = document.getElementById("arm1Input").value;
  let arm2Degrees = document.getElementById("arm2Input").value;

  sendJson(3, baseDegrees, arm1Degrees, null, null, null)
}

port.on('error', function (err) {
  console.log('Error: ', err.message)
})


animate();