<?php
/**
 * @see page.tpl.php
 */
?>

<header id="navbar" role="banner" class="navbar navbar-fixed-top">
  <div class="navbar-inner">
    <div class="container">
      <!-- .btn-navbar is used as the toggle for collapsed navbar content -->
      <a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </a>

      <?php if (!empty($logo)): ?>
          <?php
            $expect = array('curing_guide','doctor_legend','friend_activities','hot_news','illness_diagnosis');
            if(drupal_is_front_page() || in_array(arg(0), $expect) || !user_is_logged_in()) {
              $show_big = true;
            }
            if(user_is_logged_in() && !in_array(arg(0), $expect) && !drupal_is_front_page()) {
              $show_big = false;
            }

            if(TRUE || $show_big) {
              ?>
              <a class="logo pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
              </a>
              <?php
            }else{
              ?>
              <a class="logo_user_logged pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
               <img src="/<?php echo drupal_get_path('theme', 'sbq');?>/images/xlogo_19.png"/>
               </a>
              <?php
            }


          ?>
        
      <?php endif; ?>

      <?php if (!empty($site_name)): ?>
        <h1 id="site-name">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" class="brand"><?php print $site_name; ?></a>
        </h1>
      <?php endif; ?>
    
    <?php if (!empty($site_slogan)): ?>
      <div class="site_slogan_sbq"><p class="lead"><?php print $site_slogan; ?></p></div>
    <?php endif; ?>

      <?php if (!empty($primary_nav) || !empty($secondary_nav) || !empty($page['navigation'])): ?>
        <div class="nav-collapse collapse">
          <nav role="navigation">
            <?php if (0) if (!empty($primary_nav)): ?>
              <?php print render($primary_nav); ?>
            <?php endif; ?>
            <?php if (!empty($secondary_nav)): ?>
              <?php print render($secondary_nav); ?>
            <?php endif; ?>
            <?php if (!empty($page['navigation'])): ?>
              <?php print render($page['navigation']); ?>
            <?php endif; ?>
          </nav>
        </div>
      <?php endif; ?>
    </div>
  </div>
</header>
<div class="main-container tocpic-page">

  <header role="banner" id="page-header">


    <?php //print render($page['header']); ?>
  </header> <!-- /#header -->

  <div class="row-fluid">

    <section id="sbq_topic_page">  
      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted hero-unit"><?php print render($page['highlighted']); ?></div>
      <?php endif; ?>
      <?php if (0&&!empty($breadcrumb)): print $breadcrumb; endif;?>
      <a id="main-content"></a>
      <div class="topic_title"> <span>#</span> 辩论台</div>
      <?php //print render($title_prefix); ?>
      <div class=" sbq_topic_positive_statics sbq_statics_left">
        <div class="sbq_statics_left_top"></div> 
        <?php 
            $rate_widget_id = sbq_commons_get_rid_by_name('vote_sbq_topic');
            $rate_result = rate_get_results('node', arg(1), $rate_widget_id);
            // dpm($rate_result);
        ?>
        <div class="sbq_topic_positive_statics_left" data-total=<?php echo $rate_result['count'];?> data-yes=<?php echo $rate_result['options'][1];?> style="height:<?php if($rate_result['count']==0){echo "50";} else {echo $rate_result['options'][1]/$rate_result['count']*100;}?>%">
          <span class="left_font_size"><?php print $rate_result['options'][1];?></span>力顶
        </div>
        <div class="sbq_statics_left_bottom"></div>
      </div>

      <div class="sbq_topic_your_option">
      <div class=" arrow arrow-lg" id="technology-arrow">
        <div class="sbq_topic_positive" id="sbq_topic_positive">
          <p><img src="/<?php echo drupal_get_path('module', 'sbq_commons');?>/images/d_12.png" width="30" height="29"></p>
          <span>力顶</span>
          <p>点击投票</p>
        </div>
      </div>
      <div class="sarrow arrow-lg" id="team-arrow">
        <div class="sbq_topic_negative">
          <p><img src="/<?php echo drupal_get_path('module', 'sbq_commons');?>/images/d_14.png" width="30" height="29"></p>
          <span>反对</span>
          <p>点击投票</p>
        </div>
      </div>
    </div>


    <div class="sbq_statics_right">
      <div class="sbq_statics_right_top"></div>
      <div class="sbq_topic_positive_statics_right" data-total=<?php echo $rate_result['count'];?> data-no=<?php echo $rate_result['options'][-1];?> style="height:<?php if($rate_result['count']==0){echo "50";} else {echo $rate_result['options'][-1]/$rate_result['count']*100;}?>%">
        <span class="left_font_size"><?php print $rate_result['options'][-1];?></span>反对
      </div>
      <div class="sbq_statics_right_bottom"></div>
    </div>

      <?php if (0&& !empty($title)): ?>
        <h1 class="page-header"><?php print $title; ?></h1>
      <?php endif; ?>

      <?php //print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php if (!empty($tabs)): ?>
        <?php //print render($tabs); ?>
      <?php endif; ?>
      <?php if (!empty($page['help'])): ?>
        <div class="well"><?php //print render($page['help']); ?></div>
      <?php endif; ?>
      <?php if (!empty($action_links)): ?>
        <ul class="action-links"><?php //print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
    </section>

    <?php if (0&&!empty($page['sidebar_first'])): ?>
      <aside class="span3" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside>  <!-- /#sidebar-first -->
  <?php endif; ?>  

    <?php if (0&&!empty($page['sidebar_second'])): ?>
      <aside class="span3" role="complementary">
        <?php print render($page['sidebar_second']); ?>
      </aside>  <!-- /#sidebar-second -->
    <?php endif; ?>

  </div>
</div>
<footer class="footer container">
  <?php print render($page['footer']); ?>
</footer>
