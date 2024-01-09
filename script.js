function findMinimumDistance() {
  var latitudeInput = parseFloat(document.getElementById("latitude-input").value);
  var longitudeInput = parseFloat(document.getElementById("longitude-input").value);

  // Predefined locations (latitude, longitude)
  var locations = [
    { name: "Atrij", lat: 22.58063599589715, lon: 88.37623002765551 },
    { name: "Uday", lat: 22.583250282581414, lon: 88.45095296389675 },
    { name: "Sukrit", lat: 22.949007895124804, lon: 88.41717405477634 },
    { name: "Ayantik", lat: 22.473753288783037, lon: 88.40300048630226 },
    { name: "Ayan", lat: 22.592647552490234, lon: 88.40699768066406 },
  ];

  var minDistance = Number.MAX_VALUE;
  var closestLocation = null;

  // Iterate through each location and calculate the distance
  for (var i = 0; i < locations.length; i++) {
    var loc = locations[i];
    var distance = calculateDistance(loc.lat, loc.lon, latitudeInput, longitudeInput);

    if (distance < minDistance) {
      minDistance = distance;
      closestLocation = loc;
    }
  }

  // Display the closest location and minimum distance
  if (closestLocation) {
    alert(
      "The closest location is " +
      closestLocation.name +
      " with a distance of " +
      minDistance.toFixed(2) +
      " kilometers."
    );

    // Show or hide graphs based on the closest location
    var graphs = document.getElementsByClassName("graph");
    for (var i = 0; i < graphs.length; i++) {
      if (closestLocation.name === "Uday") {
        graphs[i].style.display = "flex";
      }
      else {
        graphs[i].style.display = "none";
      }
    }
  } else {
    alert("No location found. Please try again.");
  }
}

// Haversine formula to calculate the distance between two points
function calculateDistance(lat1, lon1, lat2, lon2) {
  var earthRadius = 6371; // in kilometers
  var latDiff = toRadians(lat2 - lat1);
  var lonDiff = toRadians(lon2 - lon1);

  var a =
    Math.sin(latDiff / 2) * Math.sin(latDiff / 2) +
    Math.cos(toRadians(lat1)) * Math.cos(toRadians(lat2)) * Math.sin(lonDiff / 2) * Math.sin(lonDiff / 2);
  var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
  var distance = earthRadius * c;

  return distance;
}

function toRadians(degrees) {
  return (degrees * Math.PI) / 180;
}