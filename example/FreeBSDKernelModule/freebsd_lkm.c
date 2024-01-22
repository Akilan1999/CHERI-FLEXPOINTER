#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>

static int lkm_event_handler(struct module *module, int event_type, void *arg) {

  int retval = 0;                   // function returns an integer error code, default 0 for OK

  switch (event_type) {             // event_type is an enum; let's switch on it
    case MOD_LOAD:                  // if we're loading
      uprintf("LKM Loaded\n");      // spit out a loading message
      break;

    case MOD_UNLOAD:                // if were unloading
      uprintf("LKM Unloaded\n");    // spit out an unloading messge
      break;

    default:                        // if we're doing anything else
      retval = EOPNOTSUPP;          // return a 'not supported' error
      break;
  }

  return(retval);                   // return the appropriate value

}

static moduledata_t lkm_data = {
  "freebsd_lkm",            // Name of our module
  lkm_event_handler,        // Name of our module's 'event handler' function
  NULL                      // Ignore for now :)
};

// Register the module with the kernel using:
//  the module name
//  our recently defined moduledata_t struct with module info
//  a module type (we're daying it's a driver this time)
//  a preference as to when to load the module
DECLARE_MODULE(freebsd_lkm, lkm_data, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);