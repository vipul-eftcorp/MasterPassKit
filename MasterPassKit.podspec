Pod::Spec.new do |spec|
  spec.name                   = "MasterPassKit"
  spec.version                = "1.0.0"
  spec.summary                = "Scan to Pay In-App payments is a library supplied by EFT Corp."
  spec.description            = <<-DESC
Scan to Pay In-App payments is a library supplied by UKheshe South Africa (previously Oltio Pty Ltd) to 3rd party app developers who require in-app purchases. In order to use the library, a merchant account has to be set up on the Scan to Pay SA system.
The 3rd Party developer must be familiar with the concept of creating a code as well as getting notified of the payment. These can be found in the Scan to Pay API for Secure MOTO and Face-to-Face documents.
The library is released as a Cocoa Touch Framework, called Scan to PayKit.Framework. The following environments are currently supported:
                   DESC
  spec.homepage               = "https://developer.ukheshe.com/"
  spec.license                = { :type => "Copyright", :text => <<-LICENSE 
  Copyright 2018 Permission is granted to... 
  LICENSE
  }
  spec.author                 = { "Vipul Patel" => "vipul.patel@ukheshe.com" }
  spec.platform               = :ios
  spec.platform               = :ios, "13.4"
  spec.ios.deployment_target  = "13.4"
  spec.source                 = { :http => "https://mvn.ukheshe.rocks/artifactory/ios-release-local/eftcorp/liblite/MasterPassKit.xcframework.zip"}
  spec.documentation_url      = "https://mvn.ukheshe.rocks/artifactory/ios-release-local/eftcorp/liblite/README.md"
  spec.vendored_frameworks    = "MasterPassKit.xcframework"
end