function getStatutFilevaultField(){
    return true;
}
jQuery(function ($) {
    var ind = 0;
    var fieldName = Drupal.settings.field_name;
    var lang = Drupal.settings.language;
    initializeFilevaultFieldUi();

    Drupal.behaviors.filevault_field_ui = {
        attach: function (context) {
            initializeFilevaultFieldUi();
        }
    }

    function initializeFilevaultFieldUi() {
        var filevaultFieldEnabled = true;
        var ind = 0;
        var filevault = $('input[name="'+fieldName+'['+lang+'][filevault_id]"]').val();
        if( filevault != '' ){
            $('#files_uploaded_container div').remove();
            var ArrayUploaded = filevault.split(';');
            ArrayUploaded = jQuery.grep(ArrayUploaded, function(value) {
                return value != '';
            });
            $('input[name="'+fieldName+'['+lang+'][filevault_id]"]').val('');
            $.each(ArrayUploaded, function(index, value) {
                var file = jQuery.parseJSON(value);
                ind += 1;
                filesUploaded(ind, file);
            });
        }
    }
    // Show progress bar
        $('#filevault_core_block').bind('fileuploadstart', function() {
          $('#filevault_ui_block').removeClass('hide');
        });

     // BIND EVENT DRAGNDROP
    $('#filevault_core_block').bind('fv_upload_done', function(e, data) {
        ind += 1;
        $.each(data.result, function (index, file) {
            $('#filevault_ui_block').addClass('hide');
            filesUploaded(ind, file);
        });
    });

    $('#filevault_core_block').fileupload({
        done: function (e, data) {
            $('#filevault_ui_block').addClass('hide');
        }
    });

     // BIND EVENT MODAL INSERT (FILES ALREADY ON SERVER)
    $('#filevault-modal .insert').live('click', function (e){
        ind += 1;
        $("#filevault-modal").modal("hide");
        var file = $(this).parents('li').data('json');
        filesUploaded(ind, file);
    });
	// SIMULATE CLICK TO ADD FILE
    $('#ui_upload #dragndrop-area .pc_files a').click(function() {
         $('#edit-file').css('display' , 'block').css('visibility' , 'hidden');
        $('#edit-file').click();
    });

    function filesUploaded(ind, file) {
        if(typeof(file.name) == "undefined") {
            file.name = file.filename;   
        }
        if(typeof(file.type) == "undefined") {
            file.type = file.mime_type;   
        }
        if(typeof(file.entity) == "undefined") {
            file.entity = JSON.stringify(file);
        }
        $('#files_uploaded_container').append(
                '<div class="file ' + ind + ' file-item clearfix">'
                    + '<div class="file_icon"><i class="icon-paper-clip icon-large"></i></div>'
                    + '<div class="filename span9">' + file.name + '</div>'
                    + '<div class="insert file' + ind + ' span1"> <span class="label label-info">Insert</span></div>'
                    + '<div class="remove_file file' + ind + ' "><i class="icon-remove-sign icon-small"></i></div>'
                + '</div>');
        var uploaded = $('input[name="'+fieldName+'['+lang+'][filevault_id]"]').val();
        $('input[name="'+fieldName+'['+lang+'][filevault_id]"]').val(uploaded + file.entity + ';');
        $('#files_uploaded_container .remove_file.file' + ind).click(function(){
            DeleteFile(this);
        });
        $('#files_uploaded_container .insert.file' + ind).click(function(){
           insertContent(file);
        });
        $('#files_uploaded').removeClass('hide');
    }

    function DeleteFile(elem) {
        var index = $(elem).parent().index();
        var ArrayUploaded = $('input[name="'+fieldName+'['+lang+'][filevault_id]"]').val().split(';');
        ArrayUploaded = jQuery.grep(ArrayUploaded, function(value) {
            return value != ArrayUploaded[index];
        });
        ArrayUploaded = jQuery.grep(ArrayUploaded, function(value) {
            return value != '';
        });
        if(ArrayUploaded.length === 0) {
            $('input[name="'+fieldName+'['+lang+'][filevault_id]"]').val('');
        }
        else {
            $('input[name="'+fieldName+'['+lang+'][filevault_id]"]').val(ArrayUploaded.join(";") + ';');
        }
        $(elem).parent().hide('fast', function(){
            $(elem).parent().remove();
        });
    }

});