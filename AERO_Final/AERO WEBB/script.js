function initMap() {
    const map = new google.maps.Map(document.getElementById('map'), {
      center: { lat: 0, lng: 0 },
      zoom: 8
    });

    // Create the search box and link it to the UI element
    const searchInput = document.getElementById('search-input');
    const searchBox = new google.maps.places.SearchBox(searchInput);

    // Bias the SearchBox results towards the current map's viewport
    map.addListener('bounds_changed', function() {
      searchBox.setBounds(map.getBounds());
    });

    // Listen for the event when a user selects a prediction from the search box
    searchBox.addListener('places_changed', function() {
      const places = searchBox.getPlaces();

      if (places.length === 0) {
        return;
      }

      // Clear any existing markers on the map
      const markers = [];
      markers.forEach(function(marker) {
        marker.setMap(null);
      });

      // For each place, add a marker and center the map on the selected place
      const bounds = new google.maps.LatLngBounds();
      places.forEach(function(place) {
        if (!place.geometry || !place.geometry.location) {
          console.log('Returned place contains no geometry');
          return;
        }

        const marker = new google.maps.Marker({
          map: map,
          title: place.name,
          position: place.geometry.location
        });

        markers.push(marker);
        bounds.extend(place.geometry.location);
      });

      // Center the map on the selected place
      map.fitBounds(bounds);
    });
  }
