jQuery(function () {

    'use strict';

    // Initialize the jQuery File Upload widget:
    $('#filevault_block').fileupload({
        dataType: 'json',
        maxChunkSize: 1000000,
        done: function (e, data) {
            alert( 'done');
            $.each(data.result, function (index, file) {
                $('#filevault_block').text(file.name).appendTo($('#filevault_block'));
            });
        }
    });

});
