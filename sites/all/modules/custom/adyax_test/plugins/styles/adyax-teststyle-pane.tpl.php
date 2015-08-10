<?php
/**
 * @file
 * Default theme implementation for rendering adyax-test-style-pane panel.
 *
 * Available variables:
 * - $content: Rendered three random nodes in teaser view mode.
 *
 * - $border_width_pane: Border width for pane in px.
 *
 * @see adyax_test_adyaxteststylepane_theme()
 *
 * @ingroup themeable
 */
?>
<div style="border: <?php print $border_width_pane?>px solid black">
  <?php print $content; ?>
</div>
