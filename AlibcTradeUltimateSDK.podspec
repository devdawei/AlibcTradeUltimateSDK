
Pod::Spec.new do |s|

s.name         = 'AlibcTradeUltimateSDK'
s.summary      = '阿里百川电商SDK-iOS。解决官方不提供CocoaPods方式接入的问题。'
s.version      = '5.0.0.8'
s.license      = { :type => 'MIT', :file => 'LICENSE' }
s.authors      = { 'devdawei' => '2549129899@qq.com' }
s.homepage     = 'https://github.com/devdawei'

s.platform     = :ios
s.ios.deployment_target = '9.0'
s.requires_arc = true

s.source       = { :git => 'https://github.com/devdawei/AlibcTradeUltimateSDK.git', :tag => s.version.to_s }

s.source_files = 'temp.h'

s.frameworks = "JavaScriptCore", "AssetsLibrary", "CoreMotion", "CoreMotion", "Contacts", "ContactsUI", "AddressBook", "AddressBookUI"
s.libraries = "resolv", "icucore", "c++"
s.vendored_frameworks = "framework/*/*.framework"
s.resource_bundles = {'AlibcTradeUltimateSDK' => ['bundle/*.bundle', 'bundle/*/*.bundle']}
s.resources = ["resource/*"]

s.xcconfig = { 'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES' }

end
