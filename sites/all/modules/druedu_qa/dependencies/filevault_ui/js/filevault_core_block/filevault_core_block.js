var filevaultFieldEnabled = false;

function insertContent(file){

    if( typeof interactive_editor_enabled !== "undefined"  ){

         if( interactive_editor_enabled ){

        // interactive editor insert
        var imageTemplate = doT.template(document.getElementById('ieditor_template_image').text, undefined, undefined);
        var videoTemplate = doT.template(document.getElementById('ieditor_template_video').text, undefined, undefined);
        var documentTemplate = doT.template(document.getElementById('ieditor_template_document').text, undefined, undefined);

        if(file.type.indexOf("image") != -1){
            $('#canvas').append( imageTemplate(file) );

            $('.widget').find('.delete').click(function(e) {
                $(this).parent().remove();
            });


            return;
        }

        if(file.type.indexOf("mp4") != -1){
            $('#canvas').append( videoTemplate(file) );

            $('.widget').find('.delete').click(function(e) {
                $(this).parent().remove();
            });

            return;
        }

        $('#canvas').append( documentTemplate(file) );

        $('.widget').find('.delete').click(function(e) {
            $(this).parent().remove();
        });

    }else {

        // Ckeditor insert

        var imageTemplate = doT.template(document.getElementById('filevault_core_template_image').text, undefined, undefined);
        var videoTemplate = doT.template(document.getElementById('filevault_core_template_video').text, undefined, undefined);
        var documentTemplate = doT.template(document.getElementById('filevault_core_template_document').text, undefined, undefined);

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
  }else {

        // Ckeditor insert

        var imageTemplate = doT.template(document.getElementById('filevault_core_template_image').text, undefined, undefined);
        var videoTemplate = doT.template(document.getElementById('filevault_core_template_video').text, undefined, undefined);
        var documentTemplate = doT.template(document.getElementById('filevault_core_template_document').text, undefined, undefined);

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

jQuery(function () {

    // Initialize the jQuery File Upload widget:
    $('#filevault_core_block').fileupload({
        dataType: 'json',
        maxChunkSize: 1000000,
        dropZone: $('html'),
        done: function (e, data) {
            $('#filevault_ui_block #progress_all .bar').css('width', '0%');
            $("#filevault_core_block").trigger('fv_upload_done', data);
        },
        progressall: function (e, data) {
            var progress = parseInt(data.loaded / data.total * 100, 10);
            $('#filevault_ui_block #progress_all .bar').css('width',progress + '%');
        }
    });

    // Add the ckeditor's iframe to the dropzone after initialization
    if (typeof CKEDITOR == 'object') {
      CKEDITOR.on('instanceReady', function(e) {

        $('#filevault_core_block').fileupload({
            dropZone: $('html').add($('iframe').contents()),
            done: function (e, data) {
                $.each(data.result, function (index, file) {
                    insertContent(file);
                });
            }
        });

        // Show progress bar
        $('#filevault_core_block').bind('fileuploadstart', function() {
          $('#progress_all').show();
        });
        // Hide the progress bar
        $('#filevault_core_block').bind('fileuploaddone', function() {
          $('#progress_all').hide();
        });

        // Dropzone events
        $(document).bind('dragenter', dragenter).bind('drop', drop);
        function dragenter() {}
        function drop () {}
      });

  } // if typeof

});

