<?php

/**
 * @file
 * Default theme implementation for rendering adyax-test panel.
 *
 * Available variables:
 * - $nodes: Array of rendered three random nodes in teaser view mode.
 *
 * - $attributes: Array of attributes style setting from $vars['attributes_array']
 * in hook_preprocess_THEME_HOOK() adyax_test module.
 *
 * @see adyax_test_adyaxtest_theme()
 *
 * @ingroup themeable
 */
?>
<div <?php print $attributes; ?>>
  <?php foreach($nodes as $node): ?>
    <div class="adyaxtest">
      <?php print $node; ?>
    </div>
  <?php endforeach; ?>
</div>
