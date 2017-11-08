(function($) {

  Drupal.behaviors.readmoreExtrafield = {
    attach: function(context, settings) {

      // Provide the vertical tab summaries.
      $('fieldset#edit-readmore-extrafield', context).drupalSetSummary(function(context) {
        var vals = [];
        $('input[type=checkbox]', context).each(function() {
          if (this.checked && this.attributes['data-enabled-description']) {
            vals.push(Drupal.checkPlain(this.attributes['data-enabled-description'].value));
          } else if (!this.checked && this.attributes['data-disabled-description']) {
            vals.push(Drupal.checkPlain(this.attributes['data-disabled-description'].value));
          }
        });
        return vals.join(', ');
      });
    }
  };

})(jQuery);
