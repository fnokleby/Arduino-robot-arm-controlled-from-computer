const SerialPort = require('serialport')

var scene, renderer, camera;
var cube;
var controls;

// 30 cm == 30

var p = new THREE.Vector3(0, 0, 0);
var ax = new THREE.Vector3(0, 1, 0);

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

const loader = new THREE.TextureLoader();

var baseGeometry = new THREE.BoxGeometry(30, 1, 30);
var baseMaterial = new THREE.MeshBasicMaterial({
  map: loader.load("https://i.imgur.com/9eoVQMS.png"),
});
base = new THREE.Mesh(baseGeometry, baseMaterial);

base.position.set(0, 0, 0);
scene.add(base);

var baseServoGeometry = new THREE.BoxGeometry(4.1, 4.1, 4.1);
var baseServoMaterial = new THREE.MeshBasicMaterial({ color: 0xaaaaaa });
baseServo = new THREE.Mesh(baseServoGeometry, baseServoMaterial);

baseServo.position.set(0, 2, 0);
scene.add(baseServo);



var arm1Geometry = new THREE.BoxGeometry(1, 25, 4);
var arm1Material = new THREE.MeshBasicMaterial({ color: 0xaaaaaa });
arm1 = new THREE.Mesh(arm1Geometry, arm1Material);

arm1.position.set(0, 12.5, 0);
scene.add(arm1);

arm1.position.set(0, 4, -12.5);
arm1.rotation.x = Math.PI / 2;
arm1.rotation.z = 0;

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

  fullArm0()
  sendJson(2, null, null, null, 10, null)
}

function maxArm() {
  console.log('test')

  armTo(170, 85, 0)

  sendJson(3, 170, 85, null, 10, null)
}

function sendToPos() {
  let baseDegrees = document.getElementById("baseInput").value;
  let arm1Degrees = document.getElementById("arm1Input").value;
  let arm2Degrees = document.getElementById("arm2Input").value;

  armTo(baseDegrees, 0, 0)

  sendJson(3, baseDegrees, arm1Degrees, null, null, null)
}


// 3d model functions
function fullArm0() {
  arm1.position.set(0, 4, -12.5);
  arm1.rotation.x = Math.PI / 2;
  arm1.rotation.z = 0;
  arm1.rotation.y = 0;
  arm1.rotateAroundWorldAxis(p, ax, degreeToRad(0))
}

function degreeToRad(degree) {
  let rad = degree * Math.PI / 180
  return rad
}

function armTo(baseDegrees, arm1Degrees, arm2) {
  fullArm0()

  let baseDegreesInt = parseInt(baseDegrees)

  baseDegreesInt = baseDegreesInt * Math.PI / 180

  arm1.rotateAroundWorldAxis(p, ax, baseDegreesInt)
}

THREE.Object3D.prototype.rotateAroundWorldAxis = function () {

  var q1 = new THREE.Quaternion();
  return function (point, axis, angle) {

    q1.setFromAxisAngle(axis, angle);

    this.quaternion.multiplyQuaternions(q1, this.quaternion);

    this.position.sub(point);
    this.position.applyQuaternion(q1);
    this.position.add(point);

    return this;
  }

}();

port.on('error', function (err) {
  console.log('Error: ', err.message)
})



animate();