<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>
<header class="header navbar navbar-inverse navbar-fixed-top bs-docs-nav" id="header" role="banner">
<div class="container">
  <?php if ($logo): ?>
  <div class="navbar-header">
    <button class="navbar-toggle collapsed" type="button" data-toggle="collapse" data-target=".bs-navbar-collapse">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="header__logo" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="header__logo-image" /></a>
  </div>
  <?php endif; ?>

  <?php if ($site_name || $site_slogan): ?>
    <div class="header__name-and-slogan" id="name-and-slogan">
      <?php if ($site_name): ?>
        <h1 class="header__site-name" id="site-name">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" class="header__site-link" rel="home"><span><?php print $site_name; ?></span></a>
        </h1>
      <?php endif; ?>

      <?php if ($site_slogan): ?>
        <div class="header__site-slogan" id="site-slogan"><?php print $site_slogan; ?></div>
      <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if ($main_menu): ?>
    <nav class="header__secondary-menu navbar-collapse bs-navbar-collapse collapse" id="secondary-menu" role="navigation">
      <?php print render($primary_nav); ?>
      <?php 
      // print theme('links__system_secondary_menu', array(
      //   'links' => $secondary_menu,
      //   'attributes' => array(
      //     'class' => array('links', 'inline', 'clearfix'),
      //   ),
      //   'heading' => array(
      //     'text' => $secondary_menu_heading,
      //     'level' => 'h2',
      //     'class' => array('element-invisible'),
      //   ),
      // )); 
      ?>
    </nav>
  <?php endif; ?>

  <?php print render($page['header']); ?>
</div>
</header>       
<div id="<?php echo $page_id; ?>" class="container sbq-pages <?php echo $page_class;?>">

    <?php
      // Render the sidebars to see if there's anything in them.
      $sidebar_first  = render($page['sidebar_first']);
      $sidebar_second = render($page['sidebar_second']);
    ?>

  <div id="main" class="row">
  <div class="sbq-layout sbq-page-news-layout">

    <?php if ($sidebar_first): ?>
      <?php print $sidebar_first; ?>
    <?php endif; ?>

    <div id="content" class="column col-md-<?php print _zen_layout_col_md($columns); ?>" role="main">
      <?php print render($page['highlighted']); ?>
      <?php print $breadcrumb; ?>
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1 class="page__title title" id="page-title"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php if(arg(1) != 'register') print render($tabs); ?>
      <?php print render($page['help']); ?>
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
      <?php print $feed_icons; ?>
    </div>

 

    <?php if ($sidebar_second): ?>
      <?php print $sidebar_second; ?>
    <?php endif; ?>

    </div>

  </div>


</div>

<?php print render($page['footer']); ?>
<?php print render($page['bottom']); ?>
