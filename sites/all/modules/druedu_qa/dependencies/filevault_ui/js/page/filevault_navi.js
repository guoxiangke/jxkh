

var editing,c;

function toggle_edit(){
	
    switch(editing){
    	case true:
			c.get(0).contentEditable = true;
			c.css({background:"#eeeeee"});
			editing=false;
			break;

    	case false:
			c.get(0).contentEditable = false;
			c.css({background:"white"});
			editing=true;
        	break;
    }
}


$(function() {

	  $('.fileobject .fw_delete').click(function(e) {
	  
		  var fwpath = $(this).data('fw_path'); 
		  
		  var self = this;
	  
		  $.post("/filevault/ajax/delete", { path: fwpath })
			  .done(function(data) {
				 $(self).parents('li').remove();
			  });
			  
	  });
	  
	  $('.fileobject .filename').click(function(e) {
      
	  	// save the value
	  	//var filename = $(this).text();
		editing=true;	
     	c = $(this);
     	toggle_edit();
	
		
      });
	  
	  filename
	  
	  
	  
	  

});