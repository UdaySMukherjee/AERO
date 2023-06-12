function initMap() {
  var map = new Microsoft.Maps.Map(document.getElementById('map'), {
    credentials: 'AtM3pUo7TnWEkgsJv9YURorzYHMNJUZB6RzS3J_ozE8J9D45eImWJALbZFQDD71Y'
  });

  // Add the search location functionality
  document.getElementById('search-input').addEventListener('keypress', function (e) {
    if (e.key === 'Enter') {
      searchLocation();
    }
  });

  // Perform a search based on the chosen location from the dropdown
  document.getElementById('location-choices').addEventListener('change', function() {
    var location = this.value;
    if (location) {
      document.getElementById('search-input').value = location;
      searchLocation();
    }
  });

  function searchLocation() {
    var location = document.getElementById('search-input').value;
    Microsoft.Maps.loadModule('Microsoft.Maps.Search', function () {
      var searchManager = new Microsoft.Maps.Search.SearchManager(map);
      var requestOptions = {
        bounds: map.getBounds(),
        where: location,
        callback: function (answer, userData) {
          if (answer && answer.results && answer.results.length > 0) {
            var location = answer.results[0].location;
            map.setView({ center: location });

            // Pinpoint the location on the map
            var pin = new Microsoft.Maps.Pushpin(location, { color: 'red' });
            map.entities.push(pin);

            // Calculate the minimum distance from predefined locations
            var predefinedLocations = [
              { name: 'Location 1', coordinates: new Microsoft.Maps.Location(latitude1, longitude1) },
              { name: 'Location 2', coordinates: new Microsoft.Maps.Location(latitude2, longitude2) },
              { name: 'Location 3', coordinates: new Microsoft.Maps.Location(latitude3, longitude3) },
              { name: 'Location 4', coordinates: new Microsoft.Maps.Location(latitude4, longitude4) }
            ];

            var minDistance = Number.MAX_VALUE;
            var nearestLocation;

            for (var i = 0; i < predefinedLocations.length; i++) {
              var distance = Microsoft.Maps.SpatialMath.getDistance(location, predefinedLocations[i].coordinates);
              if (distance < minDistance) {
                minDistance = distance;
                nearestLocation = predefinedLocations[i].name;
              }
            }

            // Display the nearest location
            console.log('Nearest location: ' + nearestLocation + ', Distance: ' + minDistance + ' meters');
          }
        }
      };
      searchManager.geocode(requestOptions);
    });
  }
}
