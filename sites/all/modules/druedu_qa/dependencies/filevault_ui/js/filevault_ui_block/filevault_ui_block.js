jQuery(function() {
  function insertContent(file){

    if( interactive_editor_enabled ){

        // interactive editor insert

        var imageTemplate = doT.template(document.getElementById('ieditor_template_image').text, undefined, undefined);
        var textTemplate = doT.template(document.getElementById('ieditor_template_text').text, undefined, undefined);
        var videoTemplate = doT.template(document.getElementById('ieditor_template_video').text, undefined, undefined);
        var documentTemplate = doT.template(document.getElementById('ieditor_template_document').text, undefined, undefined);

        if(file.type == "image/png" || file.type == "image/jpeg" ){
            $('#canvas').append( imageTemplate(file) );
            return;
        }

        if(file.mime_type.indexOf("mp4") != -1){
            $('#canvas').append( videoTemplate(file) );
            return;
        }

        $('#canvas').append( documentTemplate(file) );

        $('.widget').find('.delete').click(function(e) {
            $(this).parent().remove();
        });


    }else {

        // Ckeditor insert

        var imageTemplate = doT.template(document.getElementById('filevault_block_template_image').text, undefined, undefined);
        var videoTemplate = doT.template(document.getElementById('filevault_block_template_video').text, undefined, undefined);
        var documentTemplate = doT.template(document.getElementById('filevault_block_template_document').text, undefined, undefined);


        if(file.type.indexOf("image") != -1){
            Drupal.insert.insertIntoActiveEditor(imageTemplate(file));
            return;
        }

        if(file.type.indexOf("mp4") != -1){
            Drupal.insert.insertIntoActiveEditor(videoTemplate(file));
            return;
        }

        Drupal.insert.insertIntoActiveEditor(documentTemplate(file));
    }
  }

  PrepareJsonBlockUi(8);


$('#filevault_ui_block .dropzone').click(function(e) {
  $('#edit-file').click();
});

  function PrepareJsonBlockUi(nbElem){
    jQuery.getJSON(Drupal.settings.basePath+"filevault/block/list/0/"+(nbElem), function(json) {
      var imageTemplate = doT.template(document.getElementById('filevault_block_template_image').text, undefined, undefined);
      var videoTemplate = doT.template(document.getElementById('filevault_block_template_video').text, undefined, undefined);
      var documentTemplate = doT.template(document.getElementById('filevault_block_template_document').text, undefined, undefined);
      for (var i=0;i<json.length;i++) {
        if(json[i].mime_type == "image/png" || json[i].mime_type == "image/jpeg"  ){
          var element = jQuery(imageTemplate(json[i])).data('json',json[i]);
          jQuery('#filevault_ui_block ul').prepend(element);
          continue;
        }
        if(json[i].mime_type.indexOf("mp4") != -1){
          var element = jQuery(videoTemplate(json[i])).data('json',json[i]);
          jQuery('#filevault_ui_block ul').prepend(element);
          continue;
        }
        var element = jQuery(documentTemplate(json[i])).data('json',json[i]);
        jQuery('#filevault_ui_block ul').prepend(element);
      }
    });
  }

  $('.filelist').jScrollPane();
  $('#filevault_ui_block ul.files a').live('click', function (e) {
    e.preventDefault();
    if( typeof interactive_editor_enabled !== "undefined"  ) {
      if(interactive_editor_enabled) {
        insertContent( $(this).parents('li').data('json') );
      }
      else {
        Drupal.insert.insertIntoActiveEditor( jQuery(this).parents('li').find('.payload').html() );
      }
    }
    else {
      Drupal.insert.insertIntoActiveEditor( jQuery(this).parents('li').find('.payload').html() );
    }
  });
/*

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

 */

  //refresh block ui after upload a new file
  $('#filevault_core_block').bind('fv_upload_done fileuploaddone', function(e, data) {
    $('#block-filevault-ui-filevault-ui-block .filelist .files li:last-child').fadeOut('fast', function(){
      $(this).remove();
      PrepareJsonBlockUi(1);
    });
  });

});


