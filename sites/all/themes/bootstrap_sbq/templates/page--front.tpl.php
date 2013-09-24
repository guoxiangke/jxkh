<!-- <body style="" quick-markup_injected="true" id="dummybodyid"> -->
    <a class="sr-only" href="#content">Skip navigation</a>

    <!-- Docs master nav -->
    <header class="navbar navbar-inverse navbar-fixed-top bs-docs-nav" role="banner">
  <div class="container">
    <div class="navbar-header">
      <button class="navbar-toggle" type="button" data-toggle="collapse" data-target=".bs-navbar-collapse">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
      <a href="../" class="navbar-brand">Bootstrap</a>
    </div>
    <nav class="navbar-collapse bs-navbar-collapse in" role="navigation" style="height: auto;">
      <ul class="nav navbar-nav">
        <li class="active">
          <a href="../getting-started">Getting started</a>
        </li>
        <li>
          <a href="../css">CSS</a>
        </li>
        <li>
          <a href="../components">Components</a>
        </li>
        <li>
          <a href="../javascript">JavaScript</a>
        </li>
        <li>
          <a href="../customize">Customize</a>
        </li>
      </ul>
    </nav>
  </div>
</header>


    <!-- Docs page layout -->
    

    <!-- Callout for the old docs link -->
    


    <div class="container bs-docs-container">
      <div class="row">
        <div class="col-md-3">
        	<?php print render($page['sidebar_first']); ?>
        </div>
        <div class="col-md-<?php print _bootstrap_content_col_md($columns); ?>" role="main">
            <!-- Getting started-->
            <?php print render($page['content']); ?>
  					<!-- /.bs-docs-section -->
        </div>
        <!-- <div class="col-md-4">
        </div> -->
		    <?php if (!empty($page['sidebar_second'])): ?>
		      <aside class="col-md-4" role="complementary">
		        <?php print render($page['sidebar_second']); ?>
		      </aside>  <!-- /#sidebar-second -->
		    <?php endif; ?>

      </div>
    </div>

    <!-- Footer-->
    <footer class="bs-footer" role="contentinfo">
      <div class="container">        
      </div>
    </footer>

    <!-- JS and analytics only. -->
    <!-- Bootstrap core JavaScript
================================================== -->
<!-- Placed at the end of the document so the pages load faster -->


<script src="http://platform.twitter.com/widgets.js"></script>
<script src="http://v3.bootcss.com/assets/js/holder.js"></script>

<script src="http://v3.bootcss.com/assets/js/application.js"></script>
 

</body>