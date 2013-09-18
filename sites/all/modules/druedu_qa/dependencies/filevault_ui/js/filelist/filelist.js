jQuery(function() {

  var fileindex = 0;
  var imageTemplate = doT.template(document.getElementById('filevault_template_image').text, undefined, undefined);

  jQuery.getJSON(Drupal.settings.basePath+"/filevault/block/list/0", function(json) {

    fileindex += json.length;
    for (var i=0;i<json.length;i++){
      jQuery('#filevault_block #filelist').append( imageTemplate(json[i]) );
    }

  });

  jQuery('#filevault_block button.next').click(function(e) {

    jQuery.getJSON(Drupal.settings.basePath+"/filevault/block/list/" + fileindex, function(json) {

      if(json.length > 0){
        fileindex += json.length;
        jQuery('#filevault_block #filelist').html('');
        for (var i=0;i<json.length;i++){
          jQuery('#filevault_block #filelist').append( imageTemplate(json[i]) );
        }
      }

    });

  });

  jQuery('#filevault_block button.prev').click(function(e) {

    if(fileindex == 0){
      return;
    }

    fileindex -= 8;
    if( fileindex < 0){
      fileindex = 0;
    }

    jQuery.getJSON(Drupal.settings.basePath+"/filevault/block/list/" + fileindex, function(json) {
      jQuery('#filevault_block #filelist').html('');
      for (var i=0;i<json.length;i++){
        jQuery('#filevault_block #filelist').append( imageTemplate(json[i]) );
      }
    });

  });

});
