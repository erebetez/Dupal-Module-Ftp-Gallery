

Drupal.behaviors.galleryPathUpdate = function(context) {

  $('#edit-galleryurl').change(function() {
    var currentselection = $('#edit-galleryurl option:selected').text();

    $('#dynamic-Content').load('./?q=ftpgallery/ahah/callback/' + currentselection, function(response, status, xhr) {
       if (status == "error") {
         var msg = "Sorry but there was an error: ";
         msg = msg + xhr.status + " " + xhr.statusText;
         alert('Error: ' + msg);
       }
    });
  });

};
