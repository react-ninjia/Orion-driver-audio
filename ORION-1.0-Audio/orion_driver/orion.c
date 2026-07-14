#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <sound/core.h>
#include <sound/soc.h>
#include <sound/soc-acpi.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Developer");
MODULE_DESCRIPTION("Orion: Universal Intel Lake Audio Machine Driver for Chromebooks");
MODULE_VERSION("1.1");

/* 1. ID ACPI dei chip audio tipici dei Chromebook (es. Realtek) */
static const struct acpi_device_id orion_acpi_match[] = {
    { "RTL5682", 0 }, 
    { "MX98357", 0 }, 
    { }
};
MODULE_DEVICE_TABLE(acpi, orion_acpi_match);

/* 2. Definizione dei canali digitali (DAI Links) */
static struct snd_soc_dai_link_component cpus[] = {
    { .dai_name = "snd-soc-dummy-dai" }
};

static struct snd_soc_dai_link_component codecs[] = {
    { .name = "rt5682.0-001a", .dai_name = "rt5682-aif1" }
};

static struct snd_soc_dai_link_component platforms[] = {
    { .name = "snd-soc-dummy" }
};

static struct snd_soc_dai_link orion_dai_links[] = {
    {
        .name = "Orion Jack",
        .stream_name = "Primary Audio",
        .cpus = cpus,
        .num_cpus = ARRAY_SIZE(cpus),
        .codecs = codecs,
        .num_codecs = ARRAY_SIZE(codecs),
        .platforms = platforms,
        .num_platforms = ARRAY_SIZE(platforms),
        .dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBC_CFC,
    },
};

/* 3. Definizione della scheda audio ALSA */
static struct snd_soc_card orion_card = {
    .name = "orion-audio",
    .owner = THIS_MODULE,
    .dai_link = orion_dai_links,
    .num_links = ARRAY_SIZE(orion_dai_links),
};

/* 4. Inizializzazione della scheda quando il chip viene rilevato */
static int orion_probe(struct platform_device *pdev) {
    orion_card.dev = &pdev->dev;
    dev_info(&pdev->dev, "Orion Audio: Binding with Intel Lake hardware platforms...\n");
    return devm_snd_soc_register_card(&pdev->dev, &orion_card);
}

static struct platform_driver orion_driver = {
    .driver = {
        .name = "orion_intel_lake",
        .acpi_match_table = orion_acpi_match,
    },
    .probe = orion_probe,
};

static int __init orion_init(void) {
    printk(KERN_INFO "Orion Audio: Machine subsystem v1.1 registered.\n");
    return platform_driver_register(&orion_driver);
}

static void __exit orion_exit(void) {
    platform_driver_unregister(&orion_driver);
    printk(KERN_INFO "Orion Audio: Machine subsystem unregistered.\n");
}

module_init(orion_init);
module_exit(orion_exit);

