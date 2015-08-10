<?php
/**
 * @file
 * Default theme implementation for rendering adyax-test-style-pane panel.
 *
 * Available variables:
 * - $content: Rendered panes where located in that region.
 *
 * - $border_width_pane: Border width for region in px.
 *
 * @see adyax_test_adyaxteststyleregion_theme()
 *
 * @ingroup themeable
 */
?>
<div style="border: <?php print $border_width_region?>px solid black">
  <?php print $content; ?>
</div>
